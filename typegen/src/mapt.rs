pub struct MapT<K, V>
where
    K: ToString,
    V: ToString,
{
    pub key: K,
    pub value: V,
}

impl<K, V> ToString for MapT<K, V>
where
    K: ToString,
    V: ToString,
{
    fn to_string(&self) -> String {
        let mut s = String::new();
        s += "map<";
        s += &self.key.to_string();
        s += ", ";
        s += &self.value.to_string();
        s += ">";

        s
    }
}
