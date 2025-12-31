Cub3D - Ray-Casting Engine

Bu proje, 1992 yapımı efsanevi **Wolfenstein 3D** oyunundan esinlenerek, C dili ve MiniLibX kütüphanesi ile geliştirilmiş bir 3D grafik motorudur. Temel amacı, ışın izleme (ray-casting) tekniğini kullanarak iki boyutlu bir haritadan birinci şahıs perspektifli bir görüntü elde etmektir.

---

## Özellikler

- **Pseudo-3D Görüntü:** DDA (Digital Differential Analyzer) algoritması ile gerçek zamanlı 3D illüzyonu.
- **Dinamik Hareket:** WASD tuşları ile yumuşak hareket ve ok tuşları ile kamera rotasyonu.
- **Doku Eşleme (Texture Mapping):** Kuzey, Güney, Doğu ve Batı duvarları için farklı `.xpm` doku desteği.
- **Zemin ve Tavan:** Özelleştirilebilir RGB renk kodları ile atmosferik derinlik.
- **Hata Yönetimi:** Geçersiz haritalar, açık duvarlar veya hatalı konfigürasyon dosyaları için gelişmiş kontrol mekanizması.

---

## Teknik Kazanımlar

Bu projeyi geliştirirken şu matematiksel ve teknik konseptleri uyguladım:
- **Ray-Casting Algoritması:** Her dikey piksel sütunu için oyuncunun bakış açısıyla ışınlar göndererek duvar mesafelerini hesaplama.
- **Trigonometri ve Vektörler:** Oyuncu pozisyonu, görüş düzlemi (camera plane) ve yön vektörleri arasındaki ilişkilerin yönetimi.
- **Grafik Optimizasyonu:** `mlx_put_pixel` yerine doğrudan görüntü tamponuna (image buffer) yazarak FPS artışı sağlama.
- **Parsing:** `.cub` uzantılı konfigürasyon dosyalarının okunması ve harita bütünlüğünün (enclosed by walls) doğrulanması.

---

## Kurulum ve Kullanım

1. **Depoyu klonlayın:**
   ```bash
   git clone [https://github.com/AbdullahTahaUstunsoy/Cub3D.git](https://github.com/AbdullahTahaUstunsoy/Cub3D.git)
   cd Cub3D
2. Derleme yapın:
  make
3. Oyunu başlatın:
   ./cub3D maps/xxx.cub
