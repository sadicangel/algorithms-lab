# CRDT G-Counter and LWW-Register

Implement two simple CRDTs for eventually consistent replicated state.

## Tasks

- Implement a G-Counter (grow-only counter) with merge semantics.
- Implement a Last-Write-Wins register with timestamps or versions.
- Simulate multiple replicas and random merges to validate convergence.

## Suggested Languages

- Rust
- Kotlin
- C#

## Real-World Use Cases

- Model counters (likes, views) replicated across multiple nodes.
- Experiment with simple eventually-consistent state without strong coordination.

## References / Further Reading

- Introductory articles on CRDTs and eventually consistent systems.
- Distributed systems references that explain vector clocks and versioning.
