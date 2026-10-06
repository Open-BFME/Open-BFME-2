"""Declaration-only specializations must not masquerade as recovered bodies."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from find_declared_unmatched import find_defined_functions


@pytest.mark.parametrize("newline", ["\n", "\r\n", "\r\r\n"])
def test_multiline_tree_specializations_are_declarations(newline):
    source = """template <> _STL::_Rb_tree_node<ByteDwordValue> *
ByteDwordTree::_M_copy(_STL::_Rb_tree_node<ByteDwordValue> *x,
    _STL::_Rb_tree_node<ByteDwordValue> *p);
template <> _STL::_Rb_tree_node<ByteWordValue> *
ByteWordTree::_M_copy(_STL::_Rb_tree_node<ByteWordValue> *x,
    _STL::_Rb_tree_node<ByteWordValue> *p);
void Worker::run()
{
    perform();
}
"""
    assert find_defined_functions(source.replace("\n", newline)) == {
        ("Worker", "run", None)
    }


def test_real_multiline_definition_and_constructor_are_still_found():
    source = """Node *Tree::copy(Node *x,
    Node *parent) throw()
{
    return clone(x, parent);
}
Tree::Tree(int value,
    const char *name)
    : Base(value), member(name)
{
}
"""
    assert find_defined_functions(source) == {
        ("Tree", "copy", None), ("Tree", "Tree", None)
    }


def test_comments_literals_and_nested_defaults_do_not_hide_a_definition():
    source = '''void Worker::run(const char *name = "); {", // );
    int n = make_value(1, 2)) /* ; */
{
    perform(n);
}
'''
    assert find_defined_functions(source) == {("Worker", "run", None)}


def test_suffix_and_comment_punctuation_do_not_turn_a_prototype_into_a_body():
    source = '''Node *Tree::copy(Node *x, // { }
    Node *parent) throw(/* { */);
'''
    assert find_defined_functions(source) == set()


def test_declaration_annotation_cannot_excuse_a_later_definition():
    source = """// ?declared@Worker@@QAEXXZ present-unmatched
void Worker::declared(int x,
    int y);
void Worker::unclaimed()
{
}
"""
    assert find_defined_functions(source) == {("Worker", "unclaimed", None)}


def test_incomplete_signature_is_not_silently_excused():
    assert find_defined_functions("void Worker::unclaimed(\n") == {
        ("Worker", "unclaimed", None)
    }


def test_single_line_bodies_are_retained_but_prototypes_and_calls_are_not():
    source = """void Worker::declared();
void Worker::run() { perform(); }
    BASECLASS::Read(buffer, size);
"""
    assert find_defined_functions(source) == {("Worker", "run", None)}
