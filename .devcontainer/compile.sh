#!/bin/bash

# Función para compilar, ejecutar y limpiar archivos C
compile() {
    if [ "$#" -ne 1 ]; then
        echo "Uso: compile <nombre_archivo_fuente_c>"
        echo "Ejemplo: compile main.c"
        return 1
    fi

    local source_file="$1"
    local base_name=$(basename -- "$source_file")
    local file_extension="${base_name##*.}"
    local output_binary="${base_name%.*}.out" # Nombre del binario: ej. main.c -> main.out

    echo "----------------------------------------"
    echo "Procesando archivo C: $source_file"
    echo "----------------------------------------"

    # Verificar que sea un archivo C
    if [ "$file_extension" != "c" ]; then
        echo "Error: Tipo de archivo no soportado. Esta función es solo para archivos .c"
        return 1
    fi

    echo "Compilando con gcc..."
    # Eliminar binarios anteriores con el mismo nombre si existen
    rm -f "$output_binary"

    # Compilar
    gcc "$source_file" -o "$output_binary"

    local compile_status=$?

    if [ $compile_status -eq 0 ]; then
        echo "Compilación exitosa. Ejecutando $output_binary..."
        echo "----------------------------------------"
        # Ejecutar el binario
        ./"$output_binary"
        local run_status=$?
        echo "----------------------------------------"
        echo "Ejecución finalizada (código de salida: $run_status)."
        rm -f "$output_binary"
        return $run_status
    else
        echo "Error de compilación. No se ejecutará."
        return $compile_status
    fi
}

echo "Compiler loaded"