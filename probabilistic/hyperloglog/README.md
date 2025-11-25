# HyperLogLog

Implement a cardinality estimation structure for large sets.

## Tasks

- Hash input elements and use leading-zero counts to update buckets.
- Implement the standard bias-corrected cardinality estimation formula.
- Experiment with how estimation error changes with different parameters.

## Suggested Languages

- Rust
- C++

## Real-World Use Cases

- Estimate the number of unique visitors or IDs seen in logs.
- Understand how real-world analytics systems count uniques at scale.

## References / Further Reading

- HyperLogLog papers and high-level explanations in engineering blogs.
- Approximate counting chapters in streaming algorithms references.
