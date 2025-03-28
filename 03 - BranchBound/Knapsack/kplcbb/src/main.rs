use kp::risposte;
use std::collections::VecDeque;
use utility::r#type::ArrBoolInt;
use utility::r#type::IstanzaKP;

mod kp;
mod utility;

fn main() {
    let capacity = 2821;

    let w = vec![22, 7, 16, 60, 55, 89, 86, 20, 87, 7];
    let p = vec![64.0, 28.0, 14.0, 3.0, 28.0, 26.0, 73.0, 82.0, 77.0, 18.0];

    let ikpbb = IstanzaKP::new(w, p, capacity);

    let risposta_corrente = ArrBoolInt::new(vec![0; 10], vec![false; 10]);
    let mut live_nodes = VecDeque::new();
    live_nodes.push_back(risposta_corrente.clone());

    risposte(&ikpbb, risposta_corrente, live_nodes);
}
