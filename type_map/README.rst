About
=====

This subproject describes a object structure to map different types to some values.
Types are set at compile time, but values have a runtime nature.

E.g., I want to map ``int`` to the value ``1`` and ``float`` to the ``2``:

.. code-block:: cpp

   type_map<int, int, float> m{{1, 2}};
   auto value0 = std::get<float>(m); // == 2
   auto value1 = m.as<int>(); // == 1

The first argument ``int`` is the type of runtime values, the second and the next types
are the given types.


Requirements
============

Use initializer list for type mapper construction.
Use only one implementation for ``as``.

Pass all tests.

Hints
=====

#. Are you sure you understand the need of ``type_to_index`` structure?
#. Method ``as`` works like ``std::get``.
#. `Template from template <https://stackoverflow.com/questions/7397934/calling-template-function-within-template-class>`_.
#. If you return ``auto`` is considered as returning by value, but ``decltype(auto)`` is considered as returning by reference.
