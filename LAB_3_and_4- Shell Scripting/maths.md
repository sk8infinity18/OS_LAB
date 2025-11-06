# maths.sh

```bash
a=5
b=3

sum=$((a + b))
diff=$((a - b))
prod=$((a * b))
div=$((a / b))
mod=$((a % b))

c=5.2
d=3.5

res=$(echo "$c + $d" | bc)

echo "Sum: $sum"
echo "Difference: $diff"
echo "Product: $prod"
echo "Division: $div"
echo "Modulo: $mod"

echo float sum: $res```
