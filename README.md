# memdump

**memdump** is a low-level written in C function to dump memory from specified address in memory. The function call displays on stdout bytes in hex and additional information.

## Definition:

**bool memdump(const void\* ptr, size_t bytes);**

* Returns **true** if not error occured.
* **const void\* ptr** - pointer to starting address
* **size_t bytes** - number of bytes to read

## Usage

### Example

```
int main(void) {
    memdum((void\*)&main, 256);
    return 0;
}
```

### Additional Information

Information except hexdump can be easily modified by changing defined values which are described in header file.

## Issues

Function does not check whether the pointed memory address is valid - this may raise an exception.
