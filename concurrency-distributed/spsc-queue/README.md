# Lock-Free SPSC Queue

Implement a single-producer single-consumer lock-free ring buffer.

## Tasks

- Use atomics for head/tail indices and avoid locks.
- Provide enqueue and dequeue operations that are wait-free for the producer/consumer.
- Experiment with different memory orderings if your language allows.

## Suggested Languages

- C
- C++
- Rust

## Real-World Use Cases

- Passing audio samples or events from a real-time thread to a worker thread.
- High-throughput logging or metrics pipelines.

## References / Further Reading

- Concurrency references for your chosen language (atomics and memory models).
- Articles on lock-free queues and ring-buffer designs.
