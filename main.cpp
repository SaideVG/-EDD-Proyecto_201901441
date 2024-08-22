#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // Asegúrate de tener instalada la biblioteca nlohmann/json

// Estructura para representar un usuario
struct Usuario {
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento;
    std::string correo;
    std::string contrasena;
};

// Función para cargar usuarios desde un archivo JSON
std::vector<Usuario> cargarUsuariosDesdeJSON(const std::string& rutaArchivo) {
    std::vector<Usuario> usuarios;
    std::ifstream archivo(rutaArchivo);
    nlohmann::json jsonUsuarios;

    if (archivo.is_open()) {
        archivo >> jsonUsuarios;
        for (const auto& item : jsonUsuarios) {
            Usuario usuario;
            usuario.nombres = item["nombres"];
            usuario.apellidos = item["apellidos"];
            usuario.fechaNacimiento = item["fecha_de_nacimiento"];
            usuario.correo = item["correo"];
            usuario.contrasena = item["contraseña"];
            usuarios.push_back(usuario);
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo JSON." << std::endl;
    }

    return usuarios;
}

// Función para autenticar a un usuario
bool autenticarUsuario(const std::vector<Usuario>& usuarios, const std::string& correo, const std::string& contrasena) {
    for (const auto& usuario : usuarios) {
        if (usuario.correo == correo && usuario.contrasena == contrasena) {
            return true;
        }
    }
    return false;
}

// Menú principal del programa
void mostrarMenuPrincipal() {
    std::cout << "1. Registrarse" << std::endl;
    std::cout << "2. Iniciar Sesión" << std::endl;
    std::cout << "3. Enviar Solicitud de Amistad" << std::endl;
    std::cout << "4. Ver Solicitudes de Amistad" << std::endl;
    std::cout << "5. Aceptar Solicitud de Amistad" << std::endl;
    std::cout << "6. Rechazar Solicitud de Amistad" << std::endl;
    std::cout << "7. Ver Matriz de Amistades" << std::endl;
    std::cout << "8. Crear Publicación" << std::endl;
    std::cout << "9. Ver Publicaciones" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

// Menú de administración
void mostrarMenuAdmin() {
    std::cout << "\nMenú de Administración" << std::endl;
    std::cout << "1. Cargar JSON de Usuarios" << std::endl;
    std::cout << "2. Eliminar Usuario" << std::endl;
    std::cout << "3. Generar Reportes" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

int main() {
    std::vector<Usuario> usuarios;
    std::string rutaArchivo;
    int opcion;
    std::string correo, contrasena;

    do {
        std::cout << "\nSeleccione una opción:" << std::endl;
        std::cout << "1. Menú Principal" << std::endl;
        std::cout << "2. Menú de Administración" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                int opcionMenuPrincipal;
                mostrarMenuPrincipal();
                std::cin >> opcionMenuPrincipal;
                // Aquí podrías gestionar las funcionalidades del menú principal.
                break;
            }
            case 2: {
                std::cout << "Ingrese correo de administrador: ";
                std::cin >> correo;
                std::cout << "Ingrese contraseña: ";
                std::cin >> contrasena;

                if (correo == "admin@gmail.com" && contrasena == "EDD2S2024") {
                    int opcionMenuAdmin;
                    do {
                        mostrarMenuAdmin();
                        std::cin >> opcionMenuAdmin;

                        switch (opcionMenuAdmin) {
                            case 1:
                                std::cout << "Ingrese la ruta del archivo JSON de usuarios: ";
                                std::cin >> rutaArchivo;
                                usuarios = cargarUsuariosDesdeJSON(rutaArchivo);
                                if (!usuarios.empty()) {
                                    std::cout << "Usuarios cargados correctamente." << std::endl;
                                } else {
                                    std::cout << "No se pudieron cargar los usuarios." << std::endl;
                                }
                                break;

                            case 2:
                                // Aquí podrías implementar la funcionalidad para eliminar usuarios.
                                std::cout << "Funcionalidad de eliminar usuarios." << std::endl;
                                break;

                            case 3:
                                // Aquí podrías implementar la funcionalidad para generar reportes.
                                std::cout << "Funcionalidad de generar reportes." << std::endl;
                                break;

                            case 0:
                                std::cout << "Saliendo del menú de administración..." << std::endl;
                                break;

                            default:
                                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                                break;
                        }
                    } while (opcionMenuAdmin != 0);
                } else {
                    std::cout << "Correo o contraseña de administrador incorrectos." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Saliendo..." << std::endl;
                break;

            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}
