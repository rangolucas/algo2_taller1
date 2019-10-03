#include "gtest-1.8.1/gtest.h"
#include "../src/Lista.h"

/**
 * Para correr valgrind:
 * - Seleccionar arriba a la derecha la opción "correrValgrind"
 * - Hacer build del proyecto (Ctrl+F9)
 */

TEST(lista_test, test_constructor_vacio) {
    Lista<int> l;
    ASSERT_EQ(l.longitud(), 0);
}

TEST(lista_test, test_agregar_un_elemento_adelante) {
    Lista<int> l;
    l.agregarAdelante(42);
    ASSERT_EQ(l.longitud(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, test_agregar_un_elemento_atras) {
    Lista<int> l;
    l.agregarAtras(42);
    ASSERT_EQ(l.longitud(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, test_agregar_varios_elementos_solo_adelante) {
    Lista<int> l;
    l.agregarAdelante(42);
    l.agregarAdelante(41);
    l.agregarAdelante(40);
    l.agregarAdelante(39);
    ASSERT_EQ(l.longitud(), 4);
    ASSERT_EQ(l.iesimo(0), 39);
    ASSERT_EQ(l.iesimo(1), 40);
    ASSERT_EQ(l.iesimo(2), 41);
    ASSERT_EQ(l.iesimo(3), 42);
}

TEST(lista_test, test_agregar_varios_elementos_solo_atras) {
    Lista<int> l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);
    ASSERT_EQ(l.longitud(), 4);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 43);
    ASSERT_EQ(l.iesimo(2), 44);
    ASSERT_EQ(l.iesimo(3), 45);
}

TEST(lista_test, test_agregar_varios_elementos_adelante_y_atras) {
    Lista<int> l;
    l.agregarAdelante(42);
    l.agregarAdelante(41);
    l.agregarAtras(43);
    l.agregarAdelante(40);
    l.agregarAtras(44);
    ASSERT_EQ(l.longitud(), 5);
    ASSERT_EQ(l.iesimo(0), 40);
    ASSERT_EQ(l.iesimo(1), 41);
    ASSERT_EQ(l.iesimo(2), 42);
    ASSERT_EQ(l.iesimo(3), 43);
    ASSERT_EQ(l.iesimo(4), 44);
}

TEST(lista_test, test_eliminar_elementos) {
    Lista<int> l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    l.eliminar(1);

    ASSERT_EQ(l.longitud(), 3);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);
    ASSERT_EQ(l.iesimo(2), 45);

    l.eliminar(2);

    ASSERT_EQ(l.longitud(), 2);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);

    l.eliminar(0);
    l.eliminar(0);

    ASSERT_EQ(l.longitud(), 0);
}

TEST(lista_test, test_constructor_por_copia) {
    Lista<int> l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    Lista<int> otra(l);
    ASSERT_EQ(otra.longitud(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);
}

TEST(lista_test, test_operador_asignacion) {
    Lista<int> l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    Lista<int> otra = l;
    ASSERT_EQ(otra.longitud(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);

    // test pisar memoria preexistente
    l.eliminar(0);
    otra = l;
    ASSERT_EQ(otra.longitud(), 3);

    otra = Lista<int>();
    ASSERT_EQ(otra.longitud(), 0);
}

TEST(lista_test, test_lista_de_lista) {
    Lista<int> l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    Lista<Lista<int> > ll;
    ll.agregarAtras(l);
    ll.agregarAtras(l);
    ll.agregarAtras(l);

    // test aliasing entre lista original y copias
    l.eliminar(0);
    ASSERT_EQ(ll.iesimo(0).longitud(), 4);

    // test aliasing entre elementos de lista
    ll.iesimo(0).eliminar(0);
    ASSERT_EQ(ll.iesimo(1).longitud(), 4);
}

TEST(lista_test, test_lista_elem_complejo) {
    /**
     * punto2d es una clase particular que
     * - no tiene constructor sin parámetros
     * - no se puede asignar (operator= es privado)
     */
    class punto2d {
        punto2d& operator=(const punto2d& otro);
    public:
        int x,y;
        // solo tiene constructor por parámetro, no tiene constructor default
        punto2d(int a, int b) : x(a), y(b) {}
    };

    // ¡Todo esto debe compilar!
    Lista<punto2d> l;
    punto2d p(0,1);
    l.agregarAdelante(p);
    l.agregarAdelante(punto2d(1,1));
}
