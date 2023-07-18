# demo_rs_call_cc

Here is a demo to demonstrate how to call C++ from Rust with just [cc-rs](https://github.com/rust-lang/cc-rs). The key point is to allocate all the C++ objects on the heap and convert them to `void*` and expose them to C. Cast the `void*` when calling some C++ methods from C with `reinterpret_cast`.

Make sure the calling the C++ code from C is correct then use the `cc-rs` you can access the C++ code from Rust.