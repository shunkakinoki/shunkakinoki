use clap::{Command};
extern crate open;

fn main() {
    let matches = Command::new("shunkakinoki")
        .about("Shun Kakinoki's CLI")
        .author("Shun Kakinoki <shunkakinoki@gmail.com>")
        .subcommand(Command::new("home").about("Opens shunkakinoki.com"))
        .subcommand(Command::new("cause").about("Opens cause"))
        .subcommand(Command::new("mission").about("Opens mission"))
        .subcommand(Command::new("values").about("Opens values"))
        .get_matches();

    const WEBSITE: &str = "https://shunkakinoki.com";

    match matches.subcommand() {
        Some(("home", _)) => {
            open::that(WEBSITE).unwrap();
        }
        Some(("blog", _)) => {
            open::that(format!("{}/blog", WEBSITE)).unwrap();
        }
        Some(("history", _)) => {
            open::that(format!("{}/history", WEBSITE)).unwrap();
        }
        Some(("products", _)) => {
            open::that(format!("{}/products", WEBSITE)).unwrap();
        }
        Some(("social", _)) => {
            open::that(format!("{}/social", WEBSITE)).unwrap();
        }
        Some(("cause", _)) => {
            open::that(format!("{}/cause", WEBSITE)).unwrap();
        }
        Some(("mission", _)) => {
            open::that(format!("{}/mission", WEBSITE)).unwrap();
        }
        Some(("values", _)) => {
            open::that(format!("{}/values", WEBSITE)).unwrap();
        }
        Some(("how", _)) => {
            open::that(format!("{}/cause", WEBSITE)).unwrap();
        }
        Some(("resume", _)) => {
            open::that(format!("{}/mission", WEBSITE)).unwrap();
        }
        Some(("what", _)) => {
            open::that(format!("{}/values", WEBSITE)).unwrap();
        }
        Some(("when", _)) => {
            open::that(format!("{}/cause", WEBSITE)).unwrap();
        }
        Some(("who", _)) => {
            open::that(format!("{}/mission", WEBSITE)).unwrap();
        }
        Some(("why", _)) => {
            open::that(format!("{}/values", WEBSITE)).unwrap();
        }
        Some(("where", _)) => {
            open::that(format!("{}/values", WEBSITE)).unwrap();
        }
        None => println!("No subcommand was used"),
        _ => unreachable!(),
    }
}
