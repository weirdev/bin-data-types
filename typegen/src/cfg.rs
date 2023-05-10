use strum::IntoEnumIterator;
use strum_macros::EnumIter;

#[derive(Clone, Copy, EnumIter)]
pub enum Token {
    Int32T,
    StringT,
    ListT,
    MapT,
    LCAR,
    RCAR,
    COMMA,
    SPACE,
}

impl ToString for Token {
    fn to_string(&self) -> String {
        self.to_str().to_owned()
    }
}

impl Token {
    fn match_str(&self, s: &str) -> Option<&'static str> {
        let tokstr = self.to_str();
        if s.starts_with(tokstr) {
            return Some(tokstr);
        }
        None
    }

    fn match_one(&self, s: &str) -> Option<Token> {
        for tok in Token::iter() {
            let tokstr = tok.to_str();
            if s.starts_with(tokstr) {
                return Some(tok);
            }
        }
        None
    }

    fn to_str(&self) -> &'static str {
        match self {
            Token::Int32T => "int32",
            Token::StringT => "string",
            Token::ListT => "list",
            Token::MapT => "map",
            Token::LCAR => "<",
            Token::RCAR => ">",
            Token::COMMA => ",",
            Token::SPACE => " ",
        }
    }
}

pub enum Term {
    Token(Token),
    Rule(Rule),
    Empty,
}

struct ConjTerms {
    terms: Vec<Term>,
}

pub struct Rule {
    disj_terms: Vec<ConjTerms>, // (T & T & T) | (T & T)
}

struct Ast<'a> {
    terms: &'a ConjTerms,
    children: Vec<Ast<'a>>,
}

impl Rule {
    fn match_str<'a, 'b>(&'a self, s: &'b str) -> Option<(Ast<'a>, &'b str)> {
        for conj_terms in &self.disj_terms {
            let mut mismatch = false;
            let mut ast_children: Vec<Ast<'a>> = Vec::new();
            let mut chars_consumed = 0;
            for term in conj_terms.terms.iter() {
                match term {
                    Term::Token(tok) => {
                        if let Some(tokstr) = tok.match_str(&s[chars_consumed..]) {
                            chars_consumed += tokstr.len();
                        } else {
                            mismatch = true;
                            break;
                        }
                    }
                    Term::Rule(rule) => {
                        if let Some((ast, rulestr)) = rule.match_str(&s[chars_consumed..]) {
                            chars_consumed += rulestr.len();
                            ast_children.push(ast);
                        } else {
                            mismatch = true;
                            break;
                        }
                    }
                    Term::Empty => (),
                };
            }

            if !mismatch {
                return Some((
                    Ast {
                        terms: &conj_terms,
                        children: ast_children,
                    },
                    &s[..chars_consumed],
                ));
            }
        }

        None
    }
}
