# Modular Dyanmic Text Buffer

This is a personal learning project designed to dive deep into custom data structures, manual memory management, and robust stream handling in pure C. 

It is a CLI based application that is ightweight, line-oriented text buffer. Instead of relying on lazy, oversized static arrays that waste RAM, this project builds a completely dynamic grid system on the heap using multi-level pointers (`char ***`). 

##  Why I Built This (Learning Objectives)
* **Mastering Pointers:** Moving beyond simple variables to orchestrate double and triple pointers for safe structural mutation.
* **Heap Lifecycle Management:** Ensuring every single byte allocated via `malloc` and `realloc` is tracked, resized optimally, and cleanly freed via a central cleanup sequence.

## 💾 Memory Efficiency & Optimization Under the Hood

A naive approach to a text editor grid uses fixed constraints—for example, declaring `char buffer[1000][1024]`, which immediately hogs over 1MB of stack memory regardless of whether it's empty or full. 

This engine solves that through **Precise Deep Allocation** and **Shrink-to-Fit** optimizations:

1. **Amortized Row Scaling:** When reading from a file (`LoadFromFile`), the outer array pointer dynamically doubles in capacity to prevent excessive `realloc` overhead calls, achieving an amortized O(1) scaling factor.
2. **Squeezing the Footprint:** The second a user deletes a line (`DeleteLine`) or the text parsing finishes, the program invokes a custom `ShrinkToFit` routine. This forcefully shrinks the pointer registry back down to the absolute exact number of records, zeroing out slack space.
3. **Tailored Dynamic Allocations:** Every time a string is added or edited, the buffer requests exactly `strlen(text) + 1` bytes from the operating system.


## Edge-Case Resilience (The Hard Stuff)

* **Segfault Prevention in Sorting:** Passing an array containing zeroed out or cleared elements (`NULL`) into standard sorting algorithms causes instantaneous crashes. My `Compare` function implements an exact pointer hierarchy check that pushes empty markers cleanly to the bottom of the workspace without breaking the algorithm.
* **Input Truncation Safeguards:** To stop accidental alphabetic inputs from breaking the main menu selection, the interactive console reads everything cleanly as a raw string first, loops through it via `isdigit()`, and hard-truncates the string at the very first sign of trailing text garbage before converting it with `atoi`.


## 📁 Repository Structure
* `text_buffer.h` — Blueprint interface housing macros, module signatures, and structural prototypes.
* `text_buffer.c` — Implementations of core mutations (inserts, deletions, search filters, and sorting).
* `main.c`        — The production-ready user menu command loop.
* `demo.c`        — An automated regression runner showing the entire pipeline working head-to-tail without requiring typing.

---

## 🛠️ How to Compile and Run

To compile and launch the interactive app:
```bash
gcc main.c text_buffer.c -o text_buffer
./text_buffer
