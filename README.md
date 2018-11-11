# Support Ticket Database Manager

Software system for the management of technical support tickets, which will serve the users, and optimize the existing mechanisms.
In addition, the system offers high-level overview dashboards, which manual systems do not.

---

## How to contribute?

### Code:

- Variables shall be named in lower case, words separated by underscores. Example: `my_variable`.
- Functions shall be named in lowerCamelCase. Example: `void myFunction()`.
- Structs shall be named in UpperCamelCase. Example: `struct MyStruct {}`.
- Non-business-logic modules shall be implemented via [Pimpl](https://en.wikipedia.org/wiki/Opaque_pointer), and the related functions shall be prefixed with the module name. Example: `myModule_myFunction()`.
- Maintain consistent indentation. Use 4 spaces.
- Use ANSI style braces (each `{` and `}` on its own line)
- Where relevant, prefer [`wchar_t`](https://en.wikibooks.org/wiki/C_Programming/wchar.h) over `char`. _More about unicode (wide chars): [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Sets (No Excuses!)](https://www.joelonsoftware.com/2003/10/08/the-absolute-minimum-every-software-developer-absolutely-positively-must-know-about-unicode-and-character-sets-no-excuses/)_

### Source control:

- Your code should be commited to a branch which is not `master`.
- When you're done, you shall open a pull request.
- Pull request may be merged in to master after 3 aprooving reviews by your peers.
