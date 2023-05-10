mod cfg;
mod int32t;
mod listt;
mod mapt;
mod stringt;

use crate::cfg::Rule;
use crate::cfg::Term;
use crate::cfg::Token;
use crate::int32t::Int32T;
use crate::listt::ListT;
use crate::mapt::MapT;
use crate::stringt::StringT;

fn main() {
    let inttype = Int32T {};
    println!("{}", inttype.to_string());

    let listtype = ListT { element: inttype };
    println!("{}", listtype.to_string());

    let maptype = MapT {
        key: StringT {},
        value: listtype,
    };
    println!("{}", maptype.to_string());

    let tok_seq = vec![Token::ListT, Token::LCAR, Token::StringT, Token::RCAR];
    println!(
        "{}",
        &tok_seq
            .iter()
            .map(|tok| tok.to_string())
            .fold(String::new(), |a, b| a + &b)
            .as_str()
    );

    // let primitive_type_rule = Rule {
    //     terms: vec![Term::Token(Token::Int32T), Term::Token(Token::StringT)]
    // };
}
