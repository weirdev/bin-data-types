pub struct StringT {}

impl ToString for StringT {
    fn to_string(&self) -> String {
        "string".to_owned()
    }
}
