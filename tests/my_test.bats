load harness

@test "my_test-1" {
  check 'a := 99 % 7 + 3 ' '{a → 4}'
}

@test "my_test-2" {
  check 'if (69 % 45) < 708 then b := 88 else c := 49' '{b → 88}'
}

@test "my_test-3" {
  check 'if 78 < t1 ∨ 4 > t2 then x := 98 else t2 := 39' '{x → 98}'
}

@test "my_test-4" {
  check 'x := 5 ; mul := 1 ; while x < 10 do { mul := mul * x ; x := x + 1 }' '{mul → 15120, x → 10}'
}

@test "my_test-5" {
  check 'if 73 = -73 then s := -9 * -2 else r := -70 / 7' '{r → -10}'
}

@test "my_test-6" {
  check 'while false do z := y * z / j + i ; y :=  80 + 400 / 20' '{y → 100}'
}

@test "my_test-7" {
  check 'a := 484 ; b := 300 ; while ¬ ( a < b ) do { if a > b then b := b + 459 else a := a - 300 }' '{a → 484, b → 759}'
}


@test "my_test-8" {
  check 'a := 89 ; b := -76 ; if a > b then a := 780 else b := 345 + 870 / 64' '{a → 780, b → -76}'
}

@test "my_test-9" {
  check 'x := (70 * 10); y := 608 + 80 / 20 + 456 - 99; if  x = 10 * y  then x := 600 else y := 800' '{x → 700, y → 800}'
}

