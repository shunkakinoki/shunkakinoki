use clap::{crate_version, App};
extern crate open;

fn main() {
    let matches = App::new("shunkakinoki")
        .about("Shun Kakinoki's CLI")
        .version(crate_version!())
        .author("Shun Kakinoki <shunkakinoki@gmail.com>")
        .subcommand(App::new("home").about("Opens shunkakinoki.com"))
        .subcommand(App::new("cause").about("Opens cause"))
        .subcommand(App::new("mission").about("Opens mission"))
        .subcommand(App::new("values").about("Opens values"))
        .get_matches();

    const WEBSITE: &str = "https://shunkakinoki.com";

    match matches.subcommand() {
        Some(("home", _)) => {
            open::that(WEBSITE).unwrap();
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
