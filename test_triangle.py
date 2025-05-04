import geometry

# 3–4–5 right triangle
t = geometry.Triangle(3, 4, 5)
print("Area:", t.area())         # → 6.0
print("Perimeter:", t.perimeter())  # → 12.0

# Equilateral
t2 = geometry.Triangle(5, 5, 5)
print("Area:", t2.area())        # → ~10.825317547305483
print("Perimeter:", t2.perimeter()) # → 15.0
