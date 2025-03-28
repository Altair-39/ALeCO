use std::collections::VecDeque;

use crate::utility::niceprint::*;
use crate::utility::r#type::ArrBoolInt;
use crate::utility::r#type::IstanzaKP;
use crate::utility::*;

pub fn risposte(
    ikpbb: &IstanzaKP,
    mut risposta_corrente: ArrBoolInt,
    mut live_nodes: VecDeque<ArrBoolInt>,
) {
    println!("Initial State:");
    println!("Knapsack Problem Instance: {:?}", ikpbb);
    println!("Live Node State: {:?}", live_nodes);

    print!("A [0..r) {:?}", to_string_e_node(ikpbb, &risposta_corrente));
    println!("{:?}", to_string_valori(" con ", ikpbb, &risposta_corrente));

    while let Some(e_node) = live_nodes.pop_front() {
        println!("\nProcessing Node: {:?}", e_node);

        if !rifiuta(ikpbb, &risposta_corrente, &e_node) {
            println!("Node not rejected, checking for acceptance...");
            if accetta(ikpbb, &risposta_corrente, &e_node) {
                risposta_corrente = e_node.clone(); // Clone here if necessary
                println!("Node accepted: {:?}", risposta_corrente);
                print!("A eNode {:?}", to_string_e_node(ikpbb, &e_node));
                println!("{:?}", to_string_valori(" con ", ikpbb, &e_node));
            }

            if !completo(ikpbb, &risposta_corrente, &e_node) {
                println!("Node not complete, expanding...");
                espande(e_node, &mut live_nodes);
                println!("Live Node State after expansion: {:?}", live_nodes);
            } else {
                println!("Node complete.");
                print!("C eNode {:?}", to_string_e_node(ikpbb, &e_node));
                println!("{:?}", to_string_valori(" con ", ikpbb, &e_node));
            }
        } else {
            println!("Node rejected.");
            print!("R eNode {:?}", to_string_e_node(ikpbb, &e_node));
            println!("{:?}", to_string_valori(" con ", ikpbb, &e_node));
        }
    }
}

fn rifiuta(ikpbb: &IstanzaKP, _risposta_corrente: &ArrBoolInt, node: &ArrBoolInt) -> bool {
    let fh_e_node = fh(ikpbb, node);
    let peso_node = fh_e_node.get_int();

    let c = ikpbb.get_c();

    &peso_node > c
}

fn accetta(ikpbb: &IstanzaKP, risposta_corrente: &ArrBoolInt, node: &ArrBoolInt) -> bool {
    let fh_risposta_corrente = fh(ikpbb, risposta_corrente);
    let profitto_risposta_corrente = fh_risposta_corrente.get_float();

    let fh_e_node = fh(ikpbb, node);
    let profitto_node = fh_e_node.get_float();

    profitto_risposta_corrente < profitto_node
}

fn espande(node: ArrBoolInt, live_nodes: &mut VecDeque<ArrBoolInt>) {
    let soluzione = node.get_bools();
    let j = node.get_ints().len();

    println!("Expanding node: {:?}", node);

    let mut nuova_soluzione = Vec::new();
    nuova_soluzione.extend_from_slice(soluzione);

    for &nuovo_elemento_soluzione in &[soluzione[j], !soluzione[j]] {
        let mut nuova_soluzione_copy = nuova_soluzione.clone();
        nuova_soluzione_copy[j] = nuovo_elemento_soluzione;

        let nuovo_live_node =
            ArrBoolInt::new(vec![0; nuova_soluzione_copy.len()], nuova_soluzione_copy);
        live_nodes.push_back(nuovo_live_node);
    }

    println!("Live nodes after expansion: {:?}", live_nodes);
}

fn completo(ikpbb: &IstanzaKP, risposta_corrente: &ArrBoolInt, node: &ArrBoolInt) -> bool {
    let soluzione = node.get_bools();
    let j = node.get_ints();

    let mut compl = soluzione.len() == j.len();
    println!(
        "Checking if node is complete: {:?}, solution length: {}, j length: {}",
        node,
        soluzione.len(),
        j.len()
    );

    if !compl {
        let fh_e_node = fh(ikpbb, node);
        let profitto_stimato_node = stima_costo_per_eccesso(ikpbb, &fh_e_node, node);
        let fh_risposta_corrente = fh(ikpbb, risposta_corrente);
        let profitto_risposta_corrente = fh_risposta_corrente.get_float();

        compl = profitto_risposta_corrente >= profitto_stimato_node;
    }

    println!("Completion status: {}", compl);
    compl
}
