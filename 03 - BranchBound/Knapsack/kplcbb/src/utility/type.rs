#[derive(Debug)]
pub struct GenPair<A, B> {
    first: A,
    second: B,
}

impl<A, B> GenPair<A, B> {
    pub fn pi0(&self) -> &A {
        &self.first
    }

    pub fn pi1(&self) -> &B {
        &self.second
    }
}

#[derive(Debug)]
pub struct ArrBoolInt {
    coppia: GenPair<Vec<i32>, Vec<bool>>,
}

#[derive(Debug)]
pub struct IstanzaKP {
    terna: GenPair<GenPair<Vec<i32>, Vec<f32>>, i32>,
}

impl IstanzaKP {
    pub fn new(w: Vec<i32>, p: Vec<f32>, c: i32) -> Self {
        IstanzaKP {
            terna: GenPair {
                first: GenPair {
                    first: w,
                    second: p,
                },
                second: c,
            },
        }
    }

    pub fn get_w(&self) -> &Vec<i32> {
        self.terna.pi0().pi0()
    }

    pub fn get_p(&self) -> &Vec<f32> {
        self.terna.pi0().pi1()
    }

    fn get_c(&self) -> &i32 {
        self.terna.pi1()
    }
}
