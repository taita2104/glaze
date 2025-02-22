# JSON Include System

When using JSON for configuration files it can be helpful to move object definitions into separate files. This reduces copying and the need to change inputs across multiple files.

Glaze provides a `glz::file_include` type that can be added to the meta information for an object. The key may be anything, in this example we use choose `#include` to mimic C++.

```c++
struct includer_struct {
   std::string str = "Hello";
   int i = 55;
};

template <>
struct glz::meta<includer_struct> {
   using T = includer_struct;
   static constexpr auto value = object("#include", glz::file_include{}, "str", &T::str, "i", &T::i);
};
```

When this object is parsed, when the key `#include` is encountered the associated file will be read into the local object.

```c++
includer_struct obj{};
std::string s = R"({"#include": "./obj.json", "i": 100})";
glz::read_json(obj, s);
```

This will read the `./obj.json` file into the `obj` as it is parsed. Since glaze parses in sequence, the order in which includes are listed in the JSON file is the order in which they will be evaluated. The `file_include` will only be read into the local object, so includes can be deeply nested.

> Paths are always relative to the location of the previously loaded file. For nested includes this means the user only needs to consider the relative path to the file in which the include is written.
