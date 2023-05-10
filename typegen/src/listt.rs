pub struct ListT<E>
where
    E: ToString,
{
    pub element: E,
}

impl<E> ToString for ListT<E>
where
    E: ToString,
{
    fn to_string(&self) -> String {
        let mut s = String::new();
        s += "list<";
        s += &self.element.to_string();
        s += ">";

        s
    }
}
