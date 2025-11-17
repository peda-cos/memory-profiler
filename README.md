# Memory Profiler

A comprehensive C memory profiling library that intercepts and tracks dynamic memory allocations (malloc, calloc, realloc, free) to detect memory leaks and provide detailed memory usage statistics. This library uses LD_PRELOAD to hook into standard memory functions without requiring code modifications.

## Technology Stack

- **Language**: C (C11 standard)
- **Compiler**: GCC/Clang
- **Build System**: Make
- **Platform**: Linux/Unix-based systems
- **Dependencies**:
  - GNU C Library (glibc)
  - libdl (dynamic linking)
  - POSIX threads support

## Project Architecture

The Memory Profiler follows a modular architecture with clear separation of concerns:

### Core Components

- **Hooks Layer** (`hooks.c`, `malloc_hook.c`, `free_hook.c`, `calloc_hook.c`, `realloc_hook.c`)
  - Intercepts standard memory allocation functions using `LD_PRELOAD` and `dlsym`
  - Thread-safe hook management to prevent recursive calls
  - Delegates to real libc functions after tracking

- **Tracking System** (`tracking.c`, `tracking_ops.c`)
  - Maintains allocation records with metadata (address, size, timestamp, backtrace)
  - Tracks allocation/deallocation statistics
  - Provides query interface for allocation information

- **Hash Table** (`hashtable.c`, `hashtable_ops.c`, `hashtable_utils.c`)
  - Efficient O(1) lookup for allocation records
  - Handles collision resolution
  - Optimized for high-performance tracking

- **Leak Detection** (`leak_detector.c`, `leak_detector_ops.c`, `leak_detector_print.c`)
  - Identifies unfreed allocations at program termination
  - Generates detailed leak reports with backtraces
  - Categorizes and summarizes memory leaks

- **Reporting Engine** (`report.c`, `report_text.c`, `report_json.c`, `report_csv.c`)
  - Multi-format report generation (text, JSON, CSV)
  - Statistical summaries (peak usage, allocation counts)
  - Customizable output paths

- **Backtrace Support** (`backtrace.c`)
  - Captures call stacks for each allocation
  - Symbol resolution for readable stack traces
  - Configurable depth (up to 64 frames)

- **Filtering & Comparison** (`filter.c`, `compare.c`, `compare_ops.c`)
  - Filter allocations by size or source
  - Snapshot-based memory comparison
  - Differential analysis between program states

- **Signal Handling** (`signals.c`)
  - Graceful cleanup on program termination
  - Signal-triggered report generation
  - Handles SIGINT, SIGTERM, SIGSEGV

### Architecture Diagram

```
┌───────────────────────────────────────────────────┐
│                Application Process                │
└───────────────────────────────────────────────────┘
                         │
                         ↓ (LD_PRELOAD)
┌───────────────────────────────────────────────────┐
│               Memory Profiler Library             │
│                                                   │
│  ┌──────────────┐      ┌──────────────┐           │
│  │  Hook Layer  │ ───→ │   Tracking   │           │
│  │ (Intercept)  │      │    System    │           │
│  └──────────────┘      └──────────────┘           │
│         │                      │                  │
│         │                      ↓                  │
│         │              ┌──────────────┐           │
│         │              │  Hash Table  │           │
│         │              └──────────────┘           │
│         │                                         │
│         ↓                                         │
│  ┌──────────────┐      ┌──────────────┐           │
│  │   Real libc  │      │    Reports   │           │
│  │  Functions   │      │ (Text/JSON)  │           │
│  └──────────────┘      └──────────────┘           │
└───────────────────────────────────────────────────┘
```

## Getting Started

### Prerequisites

- GCC or Clang compiler
- GNU Make
- Linux/Unix operating system
- Development headers for glibc

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/memory-profiler.git
cd memory-profiler
```

2. Build the library:
```bash
make
```

This will create `libmemprof.so` in the project root.

### Basic Usage

To profile a program, use `LD_PRELOAD` to inject the library:

```bash
LD_PRELOAD=./libmemprof.so ./your_program
```

The profiler will automatically:
- Track all memory allocations
- Detect memory leaks at program exit
- Generate a report (default: text format to stdout)

### Configuration

Configure the profiler using environment variables:

```bash
# Set output format (TEXT, JSON, CSV)
export MEMPROF_FORMAT=JSON

# Set output file path
export MEMPROF_OUTPUT=/tmp/memory_report.json

# Disable backtrace tracking (improves performance)
export MEMPROF_BACKTRACE=0

# Set minimum allocation size to track (in bytes)
export MEMPROF_MIN_SIZE=1024
```

### Example

```bash
# Compile your program
gcc -o myapp main.c

# Run with memory profiler
LD_PRELOAD=./libmemprof.so MEMPROF_FORMAT=JSON ./myapp

# View the generated report
cat memory_report.json
```

## Project Structure

```
memory-profiler/
├── LICENSE                   # MIT License
├── Makefile                  # Build configuration
├── includes/                 # Public and internal headers
│   ├── memory_profiler.h     # Main public API
│   ├── tracking.h            # Allocation tracking structures
│   ├── hooks.h               # Hook function declarations
│   ├── leak_detector.h       # Leak detection API
│   ├── report.h              # Report generation
│   ├── hashtable.h           # Hash table for allocations
│   ├── backtrace.h           # Backtrace capture
│   ├── signals.h             # Signal handlers
│   ├── filter.h              # Allocation filtering
│   ├── compare.h             # Snapshot comparison
│   └── utils.h               # Utility functions
└── src/                      # Implementation files
    ├── init.c                # Library initialization
    ├── hooks.c               # Hook infrastructure
    ├── malloc_hook.c         # malloc interception
    ├── free_hook.c           # free interception
    ├── calloc_hook.c         # calloc interception
    ├── realloc_hook.c        # realloc interception
    ├── tracking.c            # Allocation tracking
    ├── tracking_ops.c        # Tracking operations
    ├── hashtable.c           # Hash table implementation
    ├── hashtable_ops.c       # Hash table operations
    ├── hashtable_utils.c     # Hash table utilities
    ├── backtrace.c           # Backtrace capture
    ├── leak_detector.c       # Leak detection logic
    ├── leak_detector_ops.c   # Leak detection operations
    ├── leak_detector_print.c # Leak report printing
    ├── report.c              # Report coordinator
    ├── report_text.c         # Text report generation
    ├── report_text_stats.c   # Statistics formatting
    ├── report_json.c         # JSON report generation
    ├── report_csv.c          # CSV report generation
    ├── signals.c             # Signal handler setup
    ├── filter.c              # Allocation filtering
    ├── compare.c             # Snapshot comparison
    ├── compare_ops.c         # Comparison operations
    ├── memory_utils.c        # Memory utilities
    ├── string_utils.c        # String utilities
    └── list.c                # Linked list utilities
```

## Key Features

### 1. **Comprehensive Memory Tracking**
- Tracks all dynamic memory allocations (malloc, calloc, realloc, free)
- Records allocation size, timestamp, and call stack
- Maintains detailed statistics (total allocations, peak usage, current usage)

### 2. **Memory Leak Detection**
- Automatically detects unfreed memory at program termination
- Provides detailed leak reports with source locations
- Categorizes leaks by size and frequency

### 3. **Call Stack Backtrace**
- Captures full call stack for each allocation (up to 64 frames)
- Symbol resolution for readable function names
- Helps identify exact allocation sites

### 4. **Multiple Report Formats**
- **Text**: Human-readable formatted output
- **JSON**: Machine-parseable structured data
- **CSV**: Spreadsheet-compatible data export

### 5. **Performance Optimized**
- Hash table for O(1) allocation lookup
- Thread-local storage to prevent recursive hooks
- Minimal overhead with configurable backtrace depth

### 6. **Filtering Capabilities**
- Filter allocations by minimum/maximum size
- Source-based filtering
- Focus on specific memory patterns

### 7. **Snapshot & Comparison**
- Take memory snapshots at different program states
- Compare snapshots to identify memory growth
- Differential analysis for memory debugging

### 8. **Signal Handling**
- Graceful cleanup on program termination
- Generate reports on SIGINT/SIGTERM
- Safe handling of abnormal termination

### 9. **Zero Code Modification**
- Uses LD_PRELOAD mechanism
- No recompilation of target application required
- Drop-in solution for existing binaries

## Development Workflow

### Building

```bash
# Clean build
make re

# Build only
make

# Clean object files
make clean

# Clean everything
make fclean
```

### Development Cycle

1. **Make Changes**: Edit source files in `src/` or headers in `includes/`
2. **Rebuild**: Run `make` to recompile
3. **Test**: Use `LD_PRELOAD` to test with sample programs
4. **Verify**: Check generated reports for correctness
5. **Iterate**: Repeat until feature is complete

### Adding New Features

1. Create header file in `includes/` if needed
2. Implement functionality in `src/`
3. Update `Makefile` SRCS and HEADERS variables
4. Rebuild and test thoroughly

## Coding Standards

This project follows these coding conventions:

### Style Guidelines
- **Indentation**: Tabs (width 4)
- **Brace Style**: K&R style (opening brace on same line)
- **Naming Conventions**:
  - Functions: `snake_case` (e.g., `track_allocation`)
  - Structures: `s_` prefix with typedef to `t_` (e.g., `typedef struct s_allocation t_allocation`)
  - Global variables: `g_` prefix (e.g., `g_config`)
  - Macros: `UPPER_SNAKE_CASE` (e.g., `MAX_BACKTRACE_DEPTH`)

### Code Organization
- One function per file for hooks
- Group related functionality in modules
- Keep headers minimal and focused
- Separate interface from implementation

### Best Practices
- **Thread Safety**: Use thread-local storage for hook guards
- **Memory Safety**: Always check return values from allocations
- **Error Handling**: Return error codes, avoid silent failures
- **Documentation**: Comment complex algorithms and data structures
- **Portability**: Use POSIX standards where possible

### Compilation Flags
- `-Wall -Wextra -Werror`: Enable all warnings as errors
- `-fPIC`: Position Independent Code for shared library
- `-O2`: Optimize for performance

## Testing

### Manual Testing

Test the library with sample programs:

```bash
# Create a test program with memory leaks
cat > test.c << 'EOF'
#include <stdlib.h>

int main() {
    void *leak1 = malloc(100);
    void *leak2 = malloc(200);
    void *ok = malloc(50);
    free(ok);
    return 0;
}
EOF

# Compile and test
cc -o test test.c
LD_PRELOAD=./libmemprof.so ./test
```

### Verification Steps

1. **Allocation Tracking**: Verify all allocations are recorded
2. **Leak Detection**: Ensure leaks are correctly identified
3. **Statistics**: Check that byte counts and allocation counts match
4. **Backtrace**: Verify call stacks are captured correctly
5. **Report Formats**: Test all output formats (text, JSON, CSV)
6. **Performance**: Profile with large allocation counts
7. **Thread Safety**: Test with multi-threaded applications

### Integration Testing

Test with real-world applications:

```bash
# Test with common utilities
LD_PRELOAD=./libmemprof.so ls -la
LD_PRELOAD=./libmemprof.so grep pattern file.txt
```

### Expected Output

A successful test should produce a report showing:
- Total allocations and frees
- Current and peak memory usage
- List of memory leaks (if any)
- Backtraces for each leak

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Pedro Monteiro
