use super::r#type::{ArrBoolInt, IstanzaKP};

// The function to format live nodes' state
pub fn to_string_e_node(ikpbb: &IstanzaKP, live_nodes: &ArrBoolInt) {
    println!("Knapsack Problem Instance:\n{:?}", ikpbb);
    println!("Live Node State:\n{:?}", live_nodes);
}

// The function to format the header and state information
pub fn to_string_valori(intestazione: &str, ikpbb: &IstanzaKP, stato: &ArrBoolInt) {
    println!("{}\n", intestazione);
    println!("Knapsack Problem Instance:\n{:?}", ikpbb);
    println!("State:\n{:?}", stato);
}
