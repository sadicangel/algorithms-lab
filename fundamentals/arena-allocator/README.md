# Arena / Bump Allocator

Implement a simple region-based allocator that allocates memory linearly and frees it all at once.

## Tasks

- Implement an arena that takes a backing buffer and supports alloc() calls that simply bump a pointer.
- Add a reset() that frees everything, and optionally support marks/checkpoints.
- Use it to allocate many small, short-lived objects efficiently.

## Suggested Languages

- C
- Zig
- Rust

## Real-World Use Cases

- Allocate nodes for ASTs or parse trees for a compiler front-end.
- Temporary allocations in tight loops where lifetime is well-scoped.

## References / Further Reading

- Game engine and compiler implementation articles describing arena and region allocators.
- Zig or Rust documentation that discusses custom allocators.
