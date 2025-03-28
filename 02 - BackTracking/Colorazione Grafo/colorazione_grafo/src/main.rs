use ndarray::Array2;

fn risposta(
    grafo: &Array2<bool>,
    colori: &mut Vec<i32>,
    soluzione: &mut Vec<i32>,
    j: usize,
) -> bool {
    if !completa(soluzione, j) {
        if !rifiuta(grafo, soluzione, j) {
            let mut acc = false;
            let rows = grafo.shape()[0];
            let mut i = 0;
            while i < rows && !acc {
                soluzione[i] = colori[i];
                colori.swap(i, j);
                acc = risposta(grafo, colori, soluzione, j + 1);
                colori.swap(i, j);
                i += 1;
            }
            acc
        } else {
            false
        }
    } else {
        let acc = accetta(grafo, soluzione, j);
        if acc {
            println!("{:?}", to_string(soluzione, j));
        }
        acc
    }
}

fn completa(soluzione: &[i32], j: usize) -> bool {
    j == soluzione.len()
}

fn rifiuta(grafo: &Array2<bool>, soluzione: &[i32], j: usize) -> bool {
    let mut rif = false;
    if grafo.len() > 1 && j >= 2 {
        let mut i = 0;
        while i < j && !rif {
            if grafo[(j - 1, i)] || grafo[(i, j - 1)] {
                rif = soluzione[j - 1] == soluzione[i];
            }
            i += 1;
        }
    }
    rif
}

fn accetta(grafo: &Array2<bool>, soluzione: &[i32], j: usize) -> bool {
    let mut acc = true;
    if grafo.len() > 1 && 2 <= j {
        let mut i = 0;
        while i < j && acc {
            if grafo[(j - 1, i)] || grafo[(i, j - 1)] {
                acc = soluzione[j - 1] != soluzione[i];
            }
            i += 1;
        }
    }
    acc
}

fn to_string(soluzione: &[i32], j: usize) -> String {
    let mut stringa = String::new();
    let mut i = 0;
    while i < j {
        stringa += &soluzione[i].to_string();
        i += 1;
    }
    stringa
}
fn main() {}
#[cfg(test)]
mod tests {
    use super::*;
    use ndarray::Array2;

    #[test]
    fn test_completa() {
        let soluzione = vec![1, 2, 3];
        let j = 3;
        assert!(completa(&soluzione, j));

        let j = 2;
        assert!(!completa(&soluzione, j));
    }

    #[test]
    fn test_rifiuta() {
        let grafo = Array2::<bool>::from_elem((3, 3), false);
        let soluzione = vec![1, 2, 3];
        let j = 2;
        assert!(!rifiuta(&grafo, &soluzione, j));

        let grafo = Array2::<bool>::from_elem((3, 3), true);
        let soluzione = vec![1, 1, 2];
        let j = 2;
        assert!(rifiuta(&grafo, &soluzione, j));
    }

    #[test]
    fn test_accetta() {
        let grafo = Array2::<bool>::from_elem((3, 3), false);
        let soluzione = vec![1, 2, 3];
        let j = 2;
        assert!(accetta(&grafo, &soluzione, j));

        let grafo = Array2::<bool>::from_elem((3, 3), true);
        let soluzione = vec![1, 1, 2];
        let j = 2;
        assert!(!accetta(&grafo, &soluzione, j));
    }

    #[test]
    fn test_risposta() {
        let grafo = Array2::<bool>::from_elem((3, 3), false);
        let mut colori = vec![1, 2, 3];
        let mut soluzione = vec![0, 0, 0];
        let j = 0;
        assert!(risposta(&grafo, &mut colori, &mut soluzione, j));

        let grafo = Array2::<bool>::from_elem((3, 3), true);
        let mut colori = vec![1, 2, 3];
        let mut soluzione = vec![0, 0, 0];
        let j = 0;
        assert!(!risposta(&grafo, &mut colori, &mut soluzione, j));
    }
}
