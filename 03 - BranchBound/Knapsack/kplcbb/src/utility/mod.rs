use std::{collections::VecDeque, usize};

use r#type::{ArrBoolInt, IntFloat, IstanzaKP};

pub mod niceprint;
pub mod r#type;

pub fn indice_node(_ikpbb: &IstanzaKP, _live_nodes: &VecDeque<ArrBoolInt>) -> usize {
    return 0;
}

pub fn fh(ikpbb: &IstanzaKP, node: &ArrBoolInt) -> IntFloat {
    let soluzione = node.get_bools();
    let j = node.get_ints();

    let w = ikpbb.get_w();
    let p = ikpbb.get_p();

    let mut peso_live_node: i32 = 0;
    let mut profitto_live_node: f32 = 0.0;

    for i in 0..j.len() {
        peso_live_node += if soluzione[i] { w[i] } else { 0 };
        profitto_live_node += if soluzione[i] { p[i] } else { 0.0 };
    }

    IntFloat::new(peso_live_node, profitto_live_node)
}

pub fn stima_costo_per_eccesso(
    ikpbb: &IstanzaKP,
    fh_live_node: &IntFloat,
    live_node: &ArrBoolInt,
) -> f32 {
    let w = ikpbb.get_w();
    let p = ikpbb.get_p();
    let c = ikpbb.get_c();

    let peso_live_node = fh_live_node.get_int();
    let profitto_live_node = fh_live_node.get_float();

    let soluzione = live_node.get_bools();
    let j = live_node.get_ints();

    let mut peso_stimato = peso_live_node;
    let mut profitto_stimato = profitto_live_node;
    let mut split = j.len();

    let mut incrementa = true;

    while split < soluzione.len() && incrementa {
        incrementa = peso_stimato + w[split] <= *c;
        if incrementa {
            peso_stimato += w[split];
            profitto_stimato += p[split];
            split += 1;
        } else {
            profitto_stimato += (c - peso_stimato) as f32 * (p[split] / w[split] as f32);
            break;
        }
    }
    profitto_stimato
}

pub fn espande(node: ArrBoolInt, live_nodes: &mut VecDeque<ArrBoolInt>) {
    let soluzione = node.get_bools();
    let j = node.get_ints().len();

    let mut nuova_soluzione = Vec::new();
    nuova_soluzione.extend_from_slice(soluzione);

    for &nuovo_elemento_soluzione in &[soluzione[j], !soluzione[j]] {
        let mut nuova_soluzione_copy = nuova_soluzione.clone();
        nuova_soluzione_copy[j] = nuovo_elemento_soluzione;

        let nuovo_live_node =
            ArrBoolInt::new(vec![0; nuova_soluzione_copy.len()], nuova_soluzione_copy);

        live_nodes.push_back(nuovo_live_node); // Modify live_nodes directly
    }
}
