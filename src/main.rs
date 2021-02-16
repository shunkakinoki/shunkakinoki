use clap::{crate_version, App};
use webbrowser;

fn main() {
    let matches = App::new("shunkakinoki")
        .about("Shun Kakinoki's CLI")
        .version(crate_version!())
        .author("Shun Kakinoki <shunkakinoki@gmail.com>")
        .subcommand(App::new("home").about("Opens shunkakinoki.com"))
        .get_matches();

    match matches.subcommand() {
        Some(("home", _)) => webbrowser::open("https://blog.shunkakinoki.com").is_ok(),
        None => println!("No subcommand was used"),
        _ => unreachable!(),
    }
}
