# C++ — runtime and compile-time polymorphism

Three individual CSCI 251 assignments at UOW (SIM Singapore). The sequence covers file parsing, virtual dispatch and function templates. These are different coursework problems that illustrate related design choices, not a controlled comparison of two implementations of the same system.

## Projects

| Folder | Task | Design |
|---|---|---|
| `01_file_parsing/` | Read configuration/data files and display a grid/weather forecast | Structs and free functions |
| `02_runtime_polymorphism/` | Manage and sort four shape types; compute area and containment | `ShapeTwoD` interface and virtual methods |
| `03_compile_time_polymorphism/` | Compare and measure points/lines | Templates and explicit specialisations |

## What the comparison shows

The shape program stores `ShapeTwoD*` values in one container. Calls such as `computeArea()` use the concrete shape's implementation at runtime. The virtual destructor supports deletion through the base pointer. Circle, rectangle, square and cross supply their own geometry operations.

The geometry program uses a template for `scalar_difference` and explicit `equals` specialisations. The generic `equals` is declared but not defined: using an unsupported type can fail at **link time**, rather than necessarily producing a compiler diagnostic. Specialisations exist for the four geometry types and for `int`/`double`; the latter are not exercised by the main program.

This project still uses inheritance: `Point3D` extends `Point2D`, and `Line3D` extends `Line2D`. Template dispatch does not require a common virtual interface for every participating type. That is the distinction from the shape container, rather than a claim that the third program has no inheritance.

## Build

```bash
for d in 0*/; do (cd "$d" && make); done
```

A C++11 compiler and `make` are required. The three programs were also compiled with Apple Clang using `-std=c++11 -Wall -Wextra -Wpedantic` during portfolio review. Warning-free compilation checks build health, not the correctness of every geometric or input case.

The third Makefile's `test` target depends on an instructor-supplied harness that is not included. Some runtime exercises likewise need course input files. The reports in `docs/` describe the submitted class design and file formats.

## Contribution and limits

These were individual assignments. Source files and Makefiles retain the submitted implementations, apart from previously removed student ID/header details. The cross-project comparison and corrected technical explanations in this README are later portfolio documentation.

`Cross` assumes a rectilinear polygon: its boundary check only handles horizontal/vertical edges, and containment uses integer arithmetic. It should not be treated as a general polygon library. The shape program uses owning raw pointers; input validation and ownership could be made more robust. Several headers use `using namespace std`, which exposes names to includers. Those are useful follow-up design improvements, but this repository keeps the scope of the coursework implementation.
