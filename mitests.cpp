#include "mini_test.h"
#include "correpocoyo.h"


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }


/*
 * Crea una carrera de int vacia y no agrega elementos
 */
void check_agregar_corredores3() {
    CorrePocoyo<int> carrera;

    carrera.nuevoCorredor(5);
    carrera.nuevoCorredor(3,5);
    carrera.nuevoCorredor(1,3);
    carrera.nuevoCorredor(10,1);
    carrera.nuevoCorredor(7);

    ASSERT(!carrera.esVacia());

    ASSERT_EQ(to_s(carrera), "[10, 1, 3, 5, 7]")
}

/*
 * Agrega 3 elementos y verifica que esten agregados segun lo pedido
 */
void check_se_cansa_y_agrega() {
    CorrePocoyo<int> carrera;

    carrera.nuevoCorredor(5);
    carrera.nuevoCorredor(3,5);
    carrera.nuevoCorredor(1,3);
    carrera.nuevoCorredor(10,1);
    carrera.nuevoCorredor(7);

    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 5);
    carrera.seCansa(3);

    ASSERT_EQ(to_s(carrera), "[10, 1, 5, 7]")

    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 4);
    carrera.seCansa(5);

    ASSERT_EQ(to_s(carrera), "[10, 1, 7]")
   
    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 3);
    carrera.seCansa(10);

    ASSERT_EQ(to_s(carrera), "[1, 7]");
    
    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 2);
    carrera.nuevoCorredor(8);

    ASSERT_EQ(to_s(carrera), "[1, 7, 8]")

    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 3);
    carrera.seCansa(8);

    ASSERT_EQ(to_s(carrera), "[1, 7]")

    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 2);
    carrera.seCansa(1);

    ASSERT_EQ(to_s(carrera), "[7]")

    ASSERT(!carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 1);
    carrera.seCansa(7);

    ASSERT_EQ(to_s(carrera), "[]")
    ASSERT(carrera.esVacia());
    ASSERT_EQ(carrera.tamanio(), 0);
}

void check_corredor_filmado2() {
    CorrePocoyo<int> carrera;

    carrera.nuevoCorredor(5);
    carrera.nuevoCorredor(3,5);
    carrera.nuevoCorredor(1,3);
    carrera.nuevoCorredor(10,1);
    carrera.nuevoCorredor(7);

    ASSERT_EQ(carrera.corredorFilmado(),5);
    ASSERT_EQ(to_s(carrera), "[10, 1, 3, 5, 7]")
    
    carrera.filmarProxPerdedor();

    ASSERT_EQ(carrera.corredorFilmado(),7);

    carrera.filmarProxExitoso();

    ASSERT_EQ(carrera.corredorFilmado(),5);

    carrera.filmarProxExitoso();

    ASSERT_EQ(carrera.corredorFilmado(),3);

    carrera.filmarProxExitoso();

    ASSERT_EQ(carrera.corredorFilmado(),1);

    carrera.filmarProxExitoso();

    ASSERT_EQ(carrera.corredorFilmado(),10);
}

void check_primero2() {
    CorrePocoyo<int> carrera;
    
    carrera.nuevoCorredor(5);
    carrera.nuevoCorredor(3,5);
    carrera.nuevoCorredor(1,3);
    carrera.nuevoCorredor(10,1);
    carrera.nuevoCorredor(7);

    ASSERT_EQ(to_s(carrera), "[10, 1, 3, 5, 7]")

    ASSERT_EQ(carrera.damePrimero(),1);

    carrera.nuevoCorredor(2,1);

    ASSERT_EQ(carrera.damePrimero(),2);

    carrera.nuevoCorredor(3,1);

    ASSERT_EQ(carrera.damePrimero(),2);

    carrera.seCansa(2);

    ASSERT_EQ(carrera.damePrimero(),3);
}


int main() {
    RUN_TEST(check_agregar_corredores3);
    RUN_TEST(check_se_cansa_y_agrega);
    RUN_TEST(check_corredor_filmado2);
    RUN_TEST(check_primero2);
    return 0;
}

