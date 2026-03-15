
def deg(p):
    return p.bit_length() - 1 if p > 0 else -1

def poly_to_str(p):
    if p == 0:
        return "0"
    terms = []
    for i in range(deg(p), -1, -1):
        if p >> i & 1:
            if i == 0:   terms.append("1")
            elif i == 1: terms.append("x")
            else:        terms.append(f"x^{i}")
    return " + ".join(terms)

def poly_div(a, b):
    q, r = 0, a
    while deg(r) >= deg(b):
        s = deg(r) - deg(b)
        q ^= (1 << s)
        r ^= (b << s)
    return q, r

def poly_mul(a, b):
    result, tmp = 0, a
    while b > 0:
        if b & 1:
            result ^= tmp
        tmp <<= 1
        b >>= 1
    return result

def gf2_inverse(a, m):
    LINE = "=" * 68
    DASH = "-" * 68

    print(LINE)
    print(f"  GF(2^10) Multiplicative Inverse")
    print(f"  m(x) = {poly_to_str(m)}  (= {m})")
    print(f"  a(x) = {poly_to_str(a)}  (= {a})")
    print(LINE)

    r_prev, r_cur = m, a
    t_prev, t_cur = 0, 1

    print(f"\nInit:")
    print(f"  r[0] = {poly_to_str(r_prev):40s} (= {r_prev})")
    print(f"  r[1] = {poly_to_str(r_cur):40s} (= {r_cur})")
    print(f"  t[0] = 0,  t[1] = 1")

    step = 1
    while r_cur != 0 and r_cur != 1:
        step += 1
        print(f"\n{DASH}")
        print(f"  Step {step}")
        print(DASH)

        q, r_new = poly_div(r_prev, r_cur)

        print(f"\n  Division:")
        print(f"    r[{step-2}] = {poly_to_str(r_prev):38s} (= {r_prev})")
        print(f"    r[{step-1}] = {poly_to_str(r_cur):38s} (= {r_cur})")
        print(f"    q    = {poly_to_str(q):38s} (= {q})")
        print(f"    r[{step}] = {poly_to_str(r_new):38s} (= {r_new})")

        qt = poly_mul(q, t_cur)
        t_new = t_prev ^ qt

        print(f"\n  Bezout update:")
        print(f"    t[{step-2}]    = {poly_to_str(t_prev):35s} (= {t_prev})")
        print(f"    t[{step-1}]    = {poly_to_str(t_cur):35s} (= {t_cur})")
        print(f"    q*t[{step-1}] = {poly_to_str(qt):35s} (= {qt})")
        print(f"    t[{step}]    = {poly_to_str(t_new):35s} (= {t_new})")

        r_prev, r_cur = r_cur, r_new
        t_prev, t_cur = t_cur, t_new

    print(f"\n{DASH}")

    inv = t_cur if r_cur == 1 else t_prev
    _, inv = poly_div(inv, m)

    product_full = poly_mul(a, inv)
    _, product_mod = poly_div(product_full, m)

    print(f"\n  Result:")
    print(f"    a^(-1) = {poly_to_str(inv):35s} (= {inv})")
    print(f"  Verify: a * a^(-1) mod m = {product_mod}  {'OK' if product_mod == 1 else 'FAIL'}")
    print(LINE)
    return inv


M = 0b10000001001  # x^10 + x^3 + 1 = 1033

print("\n" + "#" * 68)
print("  Extended Euclidean in GF(2^10)  |  m(x) = x^10 + x^3 + 1")
print("#" * 68 + "\n")

inv_a = gf2_inverse(523, M)
print()
inv_b = gf2_inverse(1015, M)

print("\n" + "#" * 68)
print("  Summary")
print("#" * 68)
print(f"  a = 523   ->  a^(-1) = {inv_a}")
print(f"  b = 1015  ->  b^(-1) = {inv_b}")
print("#" * 68)