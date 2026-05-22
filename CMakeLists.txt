cmake_minimum_required(VERSION 3.10)
project(hilalbis C ASM)

# Dil ayarları
enable_language(C)
enable_language(ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -O2 -Wall -Wextra")

# Dizin yapısı
set(BOOT_DIR "${CMAKE_SOURCE_DIR}/src/boot")
set(KERNEL_DIR "${CMAKE_SOURCE_DIR}/src/kernel")
set(BUILD_DIR "${CMAKE_BINARY_DIR}")

# Çıkış dizinleri
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")

# Bootloader (GRUB kullanarak)
file(GLOB_RECURSE BOOT_SOURCES "${BOOT_DIR}/*.asm")
file(GLOB_RECURSE BOOT_HEADERS "${BOOT_DIR}/*.h")

# Kernel kaynakları
file(GLOB_RECURSE KERNEL_SOURCES "${KERNEL_DIR}/*.c")
file(GLOB_RECURSE KERNEL_HEADERS "${KERNEL_DIR}/*.h")

# Kernel executable (bare metal)
add_executable(kernel.elf 
    ${BOOT_SOURCES}
    ${KERNEL_SOURCES}
)

target_include_directories(kernel.elf PRIVATE 
    "${BOOT_DIR}"
    "${KERNEL_DIR}"
)

# Linking flags
set_target_properties(kernel.elf PROPERTIES
    LINK_FLAGS "-T ${BOOT_DIR}/linker.ld -ffreestanding -O2 -nostdlib"
)

# ISO oluşturma hedefi
add_custom_target(iso
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/cmake/create_iso.cmake"
    DEPENDS kernel.elf
    COMMENT "ISO image oluşturuluyor..."
)

# QEMU ile çalıştırma
add_custom_target(qemu
    COMMAND qemu-system-x86_64 -cdrom "${BUILD_DIR}/hilalbis.iso" -m 256
    DEPENDS iso
    COMMENT "QEMU'da çalıştırılıyor..."
)

# Temizleme
add_custom_target(clean-iso
    COMMAND ${CMAKE_COMMAND} -E remove "${BUILD_DIR}/hilalbis.iso"
    COMMENT "ISO dosyası siliniyor..."
)

message(STATUS "Proje konfigürasyonu başarılı!")
message(STATUS "Build edilecek dosyalar: ${KERNEL_SOURCES}")
