# Modular B-Tree Implementation

A modular, template-based B-tree implementation in C++ with proper separation of concerns.

## Project Structure

```
├── Node.h          # Node class declaration
├── Node.cpp        # Node class implementation
├── BTree.h         # B-tree class declaration
├── BTree.cpp       # B-tree class implementation
├── main.cpp        # Demo application
├── Makefile        # Build configuration
└── README.md       # This file
```

## Features

- **Template-based**: Supports any data type for values
- **Modular design**: Separated into logical components
- **Complete B-tree operations**: Insert, remove, find
- **Memory management**: Proper cleanup and destructor implementation
- **Linked leaf nodes**: For efficient range queries
- **Debug-friendly**: Clear structure visualization

## Key Improvements Made

### 1. Modular Architecture
- Separated Node and BTree classes into different files
- Clear header/implementation separation
- Proper include guards and dependencies

### 2. Template Design
- Generic template implementation for value types
- Explicit template instantiations for common types
- Type-safe operations

### 3. Enhanced Interface
- Added `find()` method for key lookup
- Added utility methods (`empty()`, `size()`, `clear()`)
- Improved error handling and edge cases

### 4. Code Quality
- Removed hardcoded string types from Node class
- Fixed potential memory leaks
- Better const-correctness
- Improved variable naming and code organization

### 5. Build System
- Comprehensive Makefile with multiple targets
- Debug and release configurations
- Automatic dependency handling

## Usage

### Building the Project

```bash
# Build the demo
make

# Build with debug symbols
make debug

# Clean build files
make clean

# Build and run
make run
```

### Basic Usage Example

```cpp
#include "BTree.h"

int main() {
    // Create B-tree with degree 6
    BTree<std::string> btree(6);
    
    // Insert key-value pairs
    btree.set(1, "one");
    btree.set(2, "two");
    btree.set(3, "three");
    
    // Find a value
    std::string* result = btree.find(2);
    if (result) {
        std::cout << "Found: " << *result << std::endl;
    }
    
    // Remove a key
    btree.remove(1);
    
    // Print tree structure
    btree.printTree();
    
    return 0;
}
```

### Working with Different Data Types

```cpp
// String values
BTree<std::string> stringTree(4);
stringTree.set(1, "hello");

// Integer values  
BTree<int> intTree(4);
intTree.set(1, 42);

// Double values
BTree<double> doubleTree(4);
doubleTree.set(1, 3.14159);
```

## Class Overview

### Node<T> Class
- Manages individual B-tree nodes
- Handles splitting, merging, and borrowing operations
- Maintains parent-child and sibling relationships
- Template-based for generic value storage

### BTree<T> Class
- Main B-tree interface
- Manages root node and tree properties
- Provides public API for insertions, deletions, and searches
- Handles tree balancing and structural maintenance

## Node Types

- **NODE_ROOT**: Root node of the tree
- **NODE_INTERNAL**: Internal nodes with keys and child pointers
- **NODE_LEAF**: Leaf nodes with key-value pairs and sibling links

## Key Operations

1. **Insert**: Adds key-value pairs, splits nodes when full
2. **Remove**: Removes keys, handles underflow through borrowing/merging
3. **Find**: Locates values by key with O(log n) complexity
4. **Split**: Divides overfull nodes to maintain B-tree properties
5. **Merge**: Combines underfull nodes to maintain minimum capacity

## Memory Management

- Automatic cleanup in destructors
- Proper parent-child pointer management
- Sibling pointer maintenance for leaf nodes
- Prevention of memory leaks during splits and merges

## Future Enhancements

- **Range Queries**: Implement iterator-based range searching using linked leaf nodes
- **Persistence**: Add serialization/deserialization for disk storage
- **Bulk Operations**: Implement bulk insert/delete operations
- **Statistics**: Add tree statistics (height, node count, key count)
- **Custom Comparators**: Support for custom key comparison functions
- **Thread Safety**: Add thread-safe operations with proper locking
- **Memory Pool**: Implement custom memory allocation for better performance

## Performance Characteristics

- **Time Complexity**:
  - Search: O(log n)
  - Insert: O(log n)
  - Delete: O(log n)
- **Space Complexity**: O(n)
- **Tree Height**: O(log n) where n is number of keys

## Testing

The project includes a comprehensive demo in `main.cpp` that tests:
- Sequential insertions
- Tree structure visualization
- Key lookup operations
- Deletion operations
- Tree rebalancing

## Common Issues and Solutions

### Template Compilation
If you encounter template-related compilation errors:
- Ensure explicit template instantiations are included
- Check that all template methods are properly defined
- Verify header inclusions are correct

### Memory Leaks
The implementation includes proper cleanup:
- Destructors handle all dynamically allocated memory
- Parent-child relationships are properly maintained
- Sibling pointers are updated during operations

### Build Errors
If compilation fails:
- Ensure C++17 or later compiler support
- Check that all source files are present
- Verify Makefile paths are correct

## Contributing

When contributing to this project:
1. Maintain the modular structure
2. Follow existing naming conventions
3. Add appropriate template instantiations
4. Include comprehensive error handling
5. Update documentation for new features

## License

This implementation is provided as educational material and can be freely used and modified.
