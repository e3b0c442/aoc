use serde::Serialize;
use std::{env, fs, path::Path, path::PathBuf};
use tinytemplate::TinyTemplate;

static DAYS: [u8; 1] = [1];

#[derive(Serialize)]
struct LibContext {
    days: &'static [u8],
    cwd: PathBuf,
}

#[derive(Serialize)]
struct MainContext {
    day: u8,
}

static LIB_RS_TEMPLATE: &'static str = r#"
use std::error::Error;
use std::time::Instant;

{{ for day in days }}
#[path = "{cwd}/src/day{day}.rs"]
mod day{day};
{{ endfor }}

{{ for day in days }}
pub use day{day}::day{day};
{{ endfor }}
pub fn run_all(input_path: &str) -> Result<(), Box<dyn Error>> \{
    let funcs = [
        {{ for day in days -}}day{day},{{ endfor -}}
    ];
    let start = Instant::now();
    for (i, func) in funcs.iter().enumerate() \{
        func(&format!("\{}/\{}.txt", input_path, i + 1))?;
    }
    println!("All puzzles completed in \{:?}", start.elapsed());
    Ok(())
}
"#;

static DAY_MAIN_RS_TEMPLATE: &'static str = r#"
use simple_error::SimpleError;
use std::env;
use std::error::Error;

fn main() -> Result<(), Box<dyn Error>> \{
    let args = env::args().collect::<Vec<String>>();
    if let Some(path) = args.get(1) \{
        return aoc2015::day{day}(path);
    }
    Err(Box::new(SimpleError::new("No input file provided")))
}
"#;

fn main() {
    let out_dir = env::var_os("OUT_DIR").unwrap();

    let mut tt = TinyTemplate::new();
    tt.add_template("lib.rs", LIB_RS_TEMPLATE).unwrap();
    tt.add_template("day/main.rs", DAY_MAIN_RS_TEMPLATE)
        .unwrap();

    let ctx = LibContext {
        days: &DAYS,
        cwd: env::current_dir().unwrap(),
    };
    let lib_rs = tt.render("lib.rs", &ctx).unwrap();
    let lib_rs_path = Path::new(&out_dir).join("lib.rs");
    fs::write(&lib_rs_path, &lib_rs).unwrap();

    fs::create_dir_all(Path::new(&out_dir).join("bin")).unwrap();
    for day in DAYS {
        let ctx = MainContext { day };
        let main_rs = tt.render("day/main.rs", &ctx).unwrap();
        let main_rs_path = Path::new(&out_dir)
            .join("bin")
            .join(format!("day{}.rs", day));
        fs::write(&main_rs_path, &main_rs).unwrap();
    }
    println!("cargo:rerun-if-changed=build.rs");
}
