//
// Copyright (C) 2017 Kubos Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

use getopts::Options;
use std::env;
use serde_json;
use std::fs::File;
use std::io::prelude::*;
use serde_json::{Error, Value};
use std::io;

static PATH: &str = "/home/system/etc/config.json";
static IP: &str = "127.0.0.1";
const PORT: u16 = 8080;

#[derive(Debug, Deserialize)]
pub struct Address {
    ip: String,
    port: u16,
}

impl Default for Address {
    fn default() -> Self {
        Address {
            ip: IP.to_string(),
            port: PORT,
        }
    }
}

#[derive(Debug)]
pub struct Config {
    addr: Address,
    pub raw: Value,
}

impl Default for Config {
    fn default() -> Self {
        Config {
            addr: Address::default(),
            raw: json!(""),
        }
    }
}

impl Config {
    pub fn new(name: &str) -> Self {
        parse_config(name, get_config_path()).unwrap_or(Config::default())
    }

    pub fn hosturl(&self) -> String {
        format!("{}:{}", self.addr.ip, self.addr.port)
    }
}

fn get_config_path() -> String {
    let args: Vec<String> = env::args().collect();

    let mut opts = Options::new();
    opts.optopt("c", "config", "path to config file", "CONFIG");
    opts.optflag("h", "help", "print this help menu");
    let matches = match opts.parse(&args[1..]) {
        Ok(m) => m,
        Err(f) => panic!(f.to_string()),
    };
    match matches.opt_str("c") {
        Some(s) => s,
        None => PATH.to_string(),
    }
}

fn get_file_data(path: String) -> Result<String, io::Error> {
    let mut file = File::open(path)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    Ok(contents)
}

fn parse_config(name: &str, path: String) -> Result<Config, Error> {
    let contents = get_file_data(path).unwrap_or("".to_string());
    let data: Value = serde_json::from_str(&contents)?;

    let data = match data.get(name) {
        Some(d) => d,
        None => return Ok(Config::default()),
    };

    let address = match data.get("addr") {
        Some(a) => serde_json::from_value(a.clone()).unwrap_or(Address::default()),
        None => Address::default(),
    };

    Ok(Config {
        addr: address,
        raw: data.clone(),
    })
}
