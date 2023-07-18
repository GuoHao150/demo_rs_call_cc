
fn main() {
    cc::Build::new()
        .file("src/demo_play.cc")
        .cpp(true)
        .include("include")
        .flag("-std=c++17")
        .compile("demo");

    println!("cargo:rerun-if-changed=src/demo_play.cc");
    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rustc-link-lib=static=demo");
    println!("cargo:rustc-link-lib=dylib=stdc++");
}