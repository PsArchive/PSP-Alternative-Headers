# Alternative C Headers for PSP

Alternative headers to the PSPSDK headers.

## How this differ from PSPSDK headers.

This is not a complete list:

 - The headers that has a user-level and kernel-level separation are unified;
 - The headers show function items based on the software level (user or kernel)
   - The functions only available on user-level are behind a `__USER__` macro
   - The functions only available on kernel-level are behind a `__KERNEL__` macro
   - This made automatic based on the custom `lib/build.mak` and `lib/build_prx.mak` for makefile
 - Some headers has more stuff than PSPSDK because it was based on local modifications on [Adrenaline](https://github.com/isage/Adrenaline) (and I didn't have the time to send it all to PSPSDK yet).

## Why doing this

This is mostly to explore splitting the visibility of things based on software level (user/kernel). This is done in a similar fashion on the BSD world to control visibility of itens on kernel-level and user-level while sharing only one header file for both usages.

Then, I did the same on Adrenaline; doing so helped a bit with compilation, as the errors got usually happens way before linking time and the error messages on gcc are better than ld error messages.

After that, I decided to explore more this idea.

That being said, this is an experiment; and, although I'm currently keeping track of PSPSDK changes (as being a contributor as well), that is not a long-term promise as of now. If you are considering using this project on your project, take that as a big consideration. (This message will be changed if anything changes regarding that compromise with this project).

## How to use

Add this project as submodule to your project (or something similar on your setup):

```sh
git submodule add https://github.com/PsArchive/PSP-Alternative-Headers sdk
```

Then modify your project `Makefile` (assuming it is in your project's root folder):

```diff
- INCDIR = include
+ INCDIR = sdk/include include
- include $(PSPSDK)/lib/build.mak
+ include sdk/lib/build.mak
```

If you are using `CMake`, add:

1. If it is a user-level software:

```diff
+ target_compile_definitions(your_project_name PRIVATE -D__USER__)
```

2. If it is a kernel-level software:

```diff
+ target_compile_definitions(your_project_name PRIVATE -D__KERNEL__)
```

## License

This project is distributed under a [BSD-compatible license](https://github.com/pspdev/pspsdk/blob/master/LICENSE). See the `LICENSE` files for more information.