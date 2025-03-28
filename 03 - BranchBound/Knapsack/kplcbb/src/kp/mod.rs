use std::collections::LinkedList;

use crate::utility::r#type::ArrBoolInt;
use crate::utility::r#type::IstanzaKP;

fn risposte(ikpbb: IstanzaKP, risposta_corrente: ArrBoolInt, live_nodes: LinkedList<ArrBoolInt>) {}

fn e_node(
    ikpbb: IstanzaKP,
    risposta_corrente: ArrBoolInt,
    live_nodes: LinkedList<ArrBoolInt>,
) -> ArrBoolInt {
}

fn rifiuta(ikpbb: IstanzaKP, risposta_corrente: ArrBoolInt, e_node: ArrBoolInt) -> bool {}
