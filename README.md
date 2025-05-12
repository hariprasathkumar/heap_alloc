# 🧠 Heap Allocator

A lightweight, custom memory allocator implemented in C. This project provides `malloc`, `calloc`, `realloc`, and `free`-like functionality using a manually managed heap.

## 📦 Features

- Simple memory management using a static array
- Allocation (`heap_alloc`)
- Zero-initialized allocation (`heap_calloc`)
- Reallocation (`heap_realloc`)
- Deallocation with block coalescing (`heap_free`)
- Basic coalescing of adjacent free blocks for fragmentation mitigation

## 📁 Files

- `heap.c` – Core implementation of the heap allocator
- `heap.h` – Public interface for the allocator
- `main.c` – Example test file demonstrating usage
- `Makefile` – Build configuration

## 🛠️ Build

```bash
make
