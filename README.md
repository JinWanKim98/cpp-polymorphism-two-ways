# Two ways to say the same thing about different types

**Three individual C++ assignments (CSCI 251 Advanced Programming), written solo over one semester.**
All of the code here is mine.

They were set as three separate problems, and I did not notice until I put them side by side that the
second and third are the same problem solved with opposite halves of the language.

| | The problem | The mechanism | Resolved |
|---|---|---|---|
| **`01_file_parsing`** | Read four config files, build a grid, print a forecast | `struct` and free functions — no polymorphism at all | — |
| **`02_runtime_polymorphism`** | Four shapes; compute area, test point containment, sort them together | Abstract base class, four pure virtual functions | **at run time** |
| **`03_compile_time_polymorphism`** | Four geometry types; compare them, measure the difference between them | Function templates with explicit specialisation | **at compile time** |

Assignment 2 asks *"how do I hold four different shapes in one container and call the same function on
each?"* Assignment 3 asks *"how do I write one function that works on four different types?"* Those
sound identical. C++ answers them with two mechanisms that share nothing.

---

### 1. Run time: one pointer, four shapes

`ShapeTwoD` declares what every shape must be able to do and refuses to say how:

```cpp
class ShapeTwoD {
public:
    virtual ~ShapeTwoD();                                       // virtual: base-pointer delete is safe
    virtual string toString() const = 0;
    virtual double computeArea() const = 0;
    virtual bool isPointInShape(int x, int y) const = 0;
    virtual bool isPointOnShape(int x, int y) const = 0;
};
```

Everything downstream then stops caring which shape it holds. The shapes live in one container:

```cpp
vector<ShapeTwoD*> shapeList;
```

and sorting them by area is a comparison that never names a type:

```cpp
sort(shapeList.begin(), shapeList.end(),
     [](ShapeTwoD* a, ShapeTwoD* b) { return a->computeArea() > b->computeArea(); });
```

`computeArea()` means something different for each: `Circle` uses πr², `Cross` uses the **shoelace
formula** over its twelve vertices, walking each edge and accumulating a signed cross-product:

```cpp
for (int i = 0; i < 12; i++) {
    area += (x_coords[j] + x_coords[i]) * (y_coords[j] - y_coords[i]);
    j = i;
}
return fabs(area / 2.0);
```

Point containment uses **ray casting** — count how many edges a ray from the point crosses; odd means
inside. The lambda above calls neither of these by name. That is the whole point of the exercise, and
it is paid for with a vtable lookup on every call and a base class that every participating type must
inherit from.

**The cost is visible in what it cannot do.** `int` cannot inherit from `ShapeTwoD`.

---

### 2. Compile time: no base class, and it reaches types that have no base

Assignment 3 needs the same "one operation, many types" and gets it without inheritance:

```cpp
template <typename T>
double scalar_difference(const T& obj1, const T& obj2) {
    return fabs(obj1.getScalarValue() - obj2.getScalarValue());
}

template <typename T>
bool equals(const T& obj1, const T& obj2);

template <>
inline bool equals(const Point2D& obj1, const Point2D& obj2) {
    return (obj1.getX() == obj2.getX()) && (obj1.getY() == obj2.getY());
}

template <>
inline bool equals(const Line2D& obj1, const Line2D& obj2) {
    return equals(obj1.getPt1(), obj2.getPt1()) &&
           equals(obj1.getPt2(), obj2.getPt2());
}

template <>
inline bool equals(const int& obj1, const int& obj2) {
    return obj1 == obj2;
}
```

Three things here that the virtual-function version cannot do:

**`equals` is declared and deliberately left undefined.** There is no sensible default for "are these
two things equal" across arbitrary types, so the generic form is a promise with no body. A type that
has no specialisation fails at compile time rather than doing something wrong at run time.

**`Line2D`'s specialisation calls `equals` on its own points.** The composition is resolved by the
compiler picking `equals(const Point2D&)` — a line is equal when its endpoints are, and that sentence
is the implementation.

**It works on `int` and `double`, and the program never calls either.** The four `equals` calls in
`csci251_a3.cpp` are on `Point2D`, `Point3D`, `Line2D` and `Line3D`. The primitive specialisations
are three lines apiece and change nothing about the design — they are there because once the
mechanism is a template they cost nothing to write. That is the part worth noticing. In the
assignment 2 design those same three lines are not cheap, they are impossible at any price: a
primitive cannot derive from an abstract base. Templates do not ask a type to be part of a
hierarchy, only to support the operations used.

`scalar_difference` needs no specialisation at all — any type with `getScalarValue()` satisfies it.
The requirement is a shape the type must have, not an ancestor it must claim.

---

### 3. The build files record the semester better than the code does

The three Makefiles were written months apart and I did not think of them as evidence at the time:

```make
# 01 — two rules
all:
	g++ -std=c++11 main.cpp FileReader.cpp Display.cpp WeatherForecast.cpp -o csci251_a1.app
```

```make
# 03 — separate compilation, header dependencies, phony targets, warnings on
CXXFLAGS = -std=c++11 -Wall -Wextra
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) test.app $(OBJECTS)
.PHONY: all run test clean rebuild help
```

Assignment 1 rebuilds every file on every change and asks the compiler for no warnings at all.
Assignment 3 compiles each translation unit separately, rebuilds a file when a header it includes
changes, and turns `-Wall -Wextra` on. Assignment 2's Makefile is assignment 1's again — two rules,
no warnings. The change happens once, at assignment 3.

**All three compile clean under `-Wall -Wextra -Wpedantic` — zero warnings — even the two whose
Makefiles never asked for them.** That is checkable in thirty seconds and is in `How to Build` below.

---

### 4. Input that fights back

`02_runtime_polymorphism/BONUS_FEATURES.txt` is a document I wrote at the time about the parts that
were not required. The one that mattered:

Typing a letter where an integer is expected puts `cin` into a failed state, and every subsequent read
returns immediately without consuming anything — the menu loop spins forever and the program has to be
killed. The fix is three lines, and the discipline is applying them everywhere rather than once:

```cpp
cin >> x[i];
if (cin.fail()) {
    cout << "Invalid input! Please enter an integer." << endl;
    cin.clear();                // leave the failed state
    cin.ignore(10000, '\n');    // drop the offending characters
    cout << "Returning to main menu..." << endl;
    return;
}
```

Eight `cin.fail()` statements cover **36 input points at run time** — 8 for a square or rectangle's four
vertices, 24 for a cross's twelve, 3 for a circle's centre and radius, 1 for the menu itself — because
most of them sit inside the coordinate loops.

---

### Repository Structure

```
cpp-polymorphism-two-ways/
├── 01_file_parsing/               # structs, file IO, no polymorphism
├── 02_runtime_polymorphism/       # ShapeTwoD + 4 derived classes; BONUS_FEATURES.txt is mine
├── 03_compile_time_polymorphism/  # Point2D/3D, Line2D/3D, MyTemplates.h
├── docs/                          # the design report submitted with each assignment
│   ├── 01_report.pdf              # 11 pages - module architecture, file formats
│   ├── 02_report.pdf              # 10 pages - class hierarchy, file structure
│   └── 03_report.pdf              #  5 pages - class hierarchy, template functions
└── README.md
```

`docs/` holds the report I submitted alongside each assignment. They were written before this README
existed and describe each program on its own terms — the class hierarchy, the file layout, what each
module is responsible for. The comparison across the three in this README is a later reading of them.

### How to Build

```bash
git clone https://github.com/JinWanKim98/cpp-polymorphism-two-ways.git
cd cpp-polymorphism-two-ways
for d in 0*/; do (cd "$d" && make); done
```

To check the warning claim in section 3:

```bash
for d in 0*/; do
  echo -n "$d "
  (cd "$d" && g++ -std=c++11 -Wall -Wextra -Wpedantic -fsyntax-only *.cpp 2>&1 | grep -c "warning:")
done
```

All three should print `0`.

### Provenance

Three individual assignments for CSCI 251 at UOW (SIM Singapore), written solo. The source is as
submitted, with one change: my university ID number is gone — from the header comments and from the
banner each program prints at startup. Assignment 3's header carried its name and ID lines as
unfilled placeholders; those two went with it. Nothing else was edited — the code, the Makefiles and
`BONUS_FEATURES.txt` are the submitted versions. Assignment specifications, instructor-supplied test
data and sample code are not included.

Assignment 3's Makefile has a `test` target that builds against a test harness the module supplied.
That file is not in this repository, so `make test` does not run here. `make` does.

### Limitations

- **`Cross::isPointOnShape` only handles axis-aligned edges.** It tests `x1 == x2` or `y1 == y2` and
  silently reports `false` for anything diagonal. A cross is rectilinear so this is correct for the
  shape it is written for, but it is an assumption the function does not state and would not survive
  being reused on a general polygon — unlike `isPointInShape` beside it, which is general.
- **The ray-casting comparison is done in integer arithmetic**, so the crossing point is truncated
  rather than computed exactly. With integer vertices and axis-aligned edges the truncation does not
  change the parity, but on a shape with sloped edges it could put a boundary point on the wrong side.
- **`using namespace std` appears in five headers.** In a header it pushes the entire standard library
  into every file that includes it, which is the one place the directive is genuinely a problem. It
  should be in the `.cpp` files or written out at each use.
- **Assignment 1 has no classes at all** — three `struct`s and free functions. It is included because
  it is where the sequence starts, not because it demonstrates anything about polymorphism.
- **The comparison in this README is mine, made afterwards.** The assignments were set as three
  unrelated problems; nobody framed them as run-time versus compile-time dispatch, and the code
  contains no comment saying so.
