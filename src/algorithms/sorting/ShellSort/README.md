# Сортировка Шелла

**Сортировка Шелла** — алгоритм сортировки, являющийся усовершенствованным вариантом сортировки вставками. Идея метода Шелла состоит в сравнении элементов, стоящих не только рядом, но и на определённом расстоянии друг от друга. Иными словами — это сортировка вставками с предварительными «грубыми» проходами. Аналогичный метод усовершенствования пузырьковой сортировки называется сортировка расчёской.

## Типичная схема сортировки Шелла

![ShellSort](./images/Sorting_shellsort_anim.gif) 


## Плюсы и минусы

Невзирая на то, что сортировка Шелла во многих случаях медленнее, чем быстрая сортировка, она имеет ряд преимуществ:

+ отсутствие потребности в памяти под стек;
+ отсутствие деградации при неудачных наборах данных — быстрая сортировка легко деградирует до O(n²), что хуже, чем худшее гарантированное время для сортировки Шелла.

## Основные длины промежутков и сложность

Среднее время работы алгоритма зависит от длин промежутков — d, на которых будут находиться сортируемые элементы исходного массива ёмкостью N на каждом шаге алгоритма. Существует несколько подходов к выбору этих значений:

+   первоначально используемая Шеллом последовательность длин промежутков:![](./images/6787e44fb46b003c6ad48146b2a7cb601fbb4612.svg) в худшем случае, сложность алгоритма составит ![](./images/e5d43a3df904fa4d7220f5b86285298aa36d969b.svg);

+   предложенная Хиббардом последовательность: все значения ![](./images/1d0ae414fdd98fca4eb79b02aba42f8a390516c8.svg) такая последовательность шагов приводит к алгоритму сложностью ![](./images/0ff8d577486acc6b703329c55525ac87909501bf.svg);

+   предложенная Седжвиком последовательность: ![](./images/a1fe63653ace9a018f135f818bb963a2e23dc256.svg), если i четное и ![](./images/b455e9cb3e3b6a39e7a44b6121faf0d9b3e1ce14.svg), если i нечетное. При использовании таких приращений средняя сложность алгоритма составляет: ![](./images/d38fdcc1b94c0810992aeb5f393fc9823de3b1bb.svg), а в худшем случае порядка ![](./images/a0395f81d3c0239090b4f92eb4a7165626ae0af6.svg). При использовании формулы Седжвика следует остановиться на значении inc[s-1], если 3*inc[s] > size.;

+   предложенная Праттом последовательность: все значения ![](./images/7a8ba75f5e7e516b36ae619aad63fbb217581105.svg); в таком случае сложность алгоритма составляет ![](./images/ee3e458584d2200531ea0e202d9f75f75fc6abcc.svg);

+   эмпирическая последовательность Марцина Циура (последовательность A102549 в OEIS): ![](./images/79a785152eb92340d25530453b84c9dea878e65a.svg); является одной из лучших для сортировки массива ёмкостью приблизительно до 4000 элементов;

+   эмпирическая последовательность, основанная на числах Фибоначчи: ![](./images/97668832f7d61fe23be6ee2dd11667319754dfea.svg).

### Вывод

Лучшее время  | Худшее время| Среднее время              | Затраты памяти
------------- | ----------  | -------------------------- | ----------
O( log2 n)    | O(n2)       | зависит от выбранных шагов | О(n) всего, O(1) дополнительно

Доп материалы:
[Видеоразбор алгоритма](https://www.youtube.com/watch?v=7hSjLR0iM-Q)


# Выполнение кода
 Для запуска кода используйте команду:

`cmake -S . -B build && cmake --build "build" && ./build/tests/ShellSort_tests`