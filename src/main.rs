use std::os::raw::c_void;

extern "C" {
    fn play() -> c_void;
}

fn main() {
    unsafe {
        play();
    }
}
