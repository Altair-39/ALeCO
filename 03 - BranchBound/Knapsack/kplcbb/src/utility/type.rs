#[derive(Debug, Clone)]
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

#[derive(Debug, Clone)]
pub struct IntFloat {
    coppia: GenPair<i32, f32>,
}

impl IntFloat {
    pub fn new(first: i32, second: f32) -> Self {
        IntFloat {
            coppia: GenPair { first, second },
        }
    }

    pub fn get_int(&self) -> i32 {
        *self.coppia.pi0()
    }

    pub fn get_float(&self) -> f32 {
        *self.coppia.pi1()
    }
}

#[derive(Debug, Clone)]
pub struct ArrBoolInt {
    coppia: GenPair<Vec<i32>, Vec<bool>>,
}

impl ArrBoolInt {
    pub fn new(ints: Vec<i32>, bools: Vec<bool>) -> Self {
        ArrBoolInt {
            coppia: GenPair {
                first: ints,
                second: bools,
            },
        }
    }

    pub fn get_ints(&self) -> &Vec<i32> {
        self.coppia.pi0()
    }

    pub fn get_bools(&self) -> &Vec<bool> {
        self.coppia.pi1()
    }
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

    pub fn get_c(&self) -> &i32 {
        self.terna.pi1()
    }
}
