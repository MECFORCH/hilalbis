# HilalBIS - Sıfırdan Yazılmış İşletim Sistemi

HilalBIS, C ve x86-64 Assembly kullanarak sıfırdan yazılmış bir işletim sistemidir. Multiboot protokolü ile GRUB bootloader tarafından başlatılır.

## 📋 Özellikler

- ✅ x86-64 mimarisi desteği
- ✅ CMake build sistemi
- ✅ GRUB bootloader entegrasyonu
- ✅ VGA terminal çıkışı (80x25)
- ✅ Bare-metal kernel
- ✅ QEMU/VirtualBox uyumluluğu
- ✅ Multiboot protokolü desteği

## 📁 Proje Yapısı

```
hilalbis/
├── CMakeLists.txt          # Ana build konfigürasyonu
├── .gitignore              # Git ignore kuralları
├── src/
│   ├── boot/
│   │   ├── boot.s          # x86-64 Bootloader
│   │   └── linker.ld       # Linker scripti
│   └── kernel/
│       ├── kernel.c        # Kernel implementasyonu
│       └── kernel.h        # Kernel başlıkları
└── README.md               # Bu dosya
```

## 🛠️ Gereksinimler

### Linux/Ubuntu'da:
```bash
sudo apt-get update
sudo apt-get install build-essential nasm grub-pc-bin grub-efi-amd64-bin xorriso qemu-system-x86
```

### macOS'te:
```bash
brew install cmake nasm qemu grub
```

## 🔨 Derleme Adımları

```bash
# 1. Repository'yi klonla
git clone https://github.com/MECFORCH/hilalbis.git
cd hilalbis

# 2. Build dizini oluştur
mkdir build
cd build

# 3. CMake ile konfigür et
cmake ..

# 4. Kernel'i derle
cmake --build .

# 5. ISO image'ını oluştur (Linux/macOS)
make iso
```

## 🚀 Çalıştırma

### QEMU ile (Önerilir):
```bash
cd build
qemu-system-x86_64 -cdrom hilalbis.iso -m 256 -display gtk
```

### Alternatif QEMU seçenekleri:
```bash
# VNC ile
qemu-system-x86_64 -cdrom hilalbis.iso -m 256 -vnc :0

# SDL ile
qemu-system-x86_64 -cdrom hilalbis.iso -m 256 -display sdl

# Grafik olmadan (SSH gibi)
qemu-system-x86_64 -cdrom hilalbis.iso -m 256 -nographic
```

### VirtualBox ile:
1. Yeni sanal makine oluştur (Linux, 64-bit)
2. RAM: 256 MB veya daha fazla
3. Storage: Sanal disk oluştur (1 GB+)
4. Settings > Storage > CD/DVD > `hilalbis.iso` seç
5. Başlat

## 📝 Geliştirme Yol Haritası

- [x] Bootloader yapılandırması
- [x] VGA terminal sistemi
- [x] CMake build sistemi
- [ ] IDT (Interrupt Descriptor Table) kurulumu
- [ ] GDT (Global Descriptor Table)
- [ ] Memory management
- [ ] Paging sistemi
- [ ] Interrupt handling
- [ ] Keyboard driver
- [ ] Dosya sistemi (FAT32)
- [ ] Shell implementation
- [ ] Kullanıcı space
- [ ] Sistem çağrıları

## 🔍 Çıktı Örneği

QEMU'da çalıştırdığında şu şekilde görünür:

```
=================================
  HilalBIS Operating System
=================================

Kernel basladi...
Multiboot Magic: 0x2badb002

Kernel calisiyorum...
Bekleyin...
```

## 🐛 Sorun Giderme

### Derleme hatası: "cmake: command not found"
```bash
sudo apt-get install cmake
```

### Hata: "nasm: command not found"
```bash
sudo apt-get install nasm
```

### Derleme hatası: "relocation R_X86_64_32"
Bu hata, bootloader ile kernel arasında memory layout problemidir. Linker.ld dosyasını kontrol edin.

### QEMU açılmıyor
```bash
# QEMU kurulu olduğunu kontrol et
qemu-system-x86_64 --version

# Grafik desteği olmayan sistemler için
qemu-system-x86_64 -cdrom hilalbis.iso -m 256 -nographic
```

### ISO dosyası oluşturulmadı
```bash
# grub-mkrescue kurulu olduğunu kontrol et
grub-mkrescue --version

# xorriso kurulu olduğunu kontrol et
xorriso -version

# Eğer grub-mkrescue yoksa, xorriso ile manuel oluştur
xorriso -as mkisofs -R -J -b boot/grub/i386-pc/eltorito.img -no-emul-boot -boot-load-size 4 -boot-info-table -o hilalbis.iso iso/
```

## 📚 Önemli Kaynaklar

- [OSDev.org Wiki](https://wiki.osdev.org) - OS Geliştirme Kaynakları
- [CMake Documentation](https://cmake.org/documentation/) - CMake Rehberi
- [x86-64 Architecture](https://www.intel.com/content/dam/develop/external/us/en/documents/manual-vol-1.pdf) - Intel Manual
- [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) - GRUB Multiboot
- [GRUB Manual](https://www.gnu.org/software/grub/manual/) - GRUB Kullanma Kılavuzu
- [System V AMD64 ABI](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf) - x86-64 ABI

## 💡 Yararlı Komutlar

```bash
# ISO dosyasını inceleme
file hilalbis.iso

# Boot sektörü analizi
hexdump -C hilalbis.iso | head -20

# Kernel binary'sini kontrol etme
objdump -f kernel.elf
objdump -h kernel.elf
objdump -d kernel.elf | head -50

# Nm ile sembol tablosunu göster
nm kernel.elf
```

## 📄 Lisans

Bu proje açık kaynak kodludur. Özgürce kullanın, değiştirin ve geliştirin.

## 👤 Katkıcılar

- **MECFORCH** - Proje yöneticisi ve geliştirici

## 🔗 Linkler

- **GitHub Repository:** https://github.com/MECFORCH/hilalbis
- **Issues:** https://github.com/MECFORCH/hilalbis/issues
- **Discussions:** https://github.com/MECFORCH/hilalbis/discussions

---

**Başlama Tarihi:** 2026-02-10  
**Son Güncelleme:** 2026-05-22  
**Durum:** Aktif Geliştirme 🚀

---

## Notlar

Bu projede sıfırdan bir işletim sistemi geliştiriyoruz. Her aşama öğrenme ve deneme-yanılma içerir. Sorunlarla karşılaşırsanız, GitHub Issues'te açabilirsiniz.

Happy coding! 🎉
