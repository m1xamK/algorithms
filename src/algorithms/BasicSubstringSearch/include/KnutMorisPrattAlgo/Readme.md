
## Алгоритм Кнута-Морриса-Пратта

<h2 id="ustroystvo-algoritma">Устройство алгоритма</h2><br>
<h3 id="grani-stroki">Грани строки</h3><br>
<p>Начать стоит с того, что у строки есть грани. Гранью строки называется любой префикс строки, который равен ее суффиксу.</p><br>
<p>Например, у строки <em>qwertyqwe</em> есть грань <em>qwe</em>, потому что строка и начинается, и заканчивается на <em>qwe</em>. Важно заметить, что грань не может быть равна самой строке.</p><br>
<p>Таким образом для строки <em>aaaaa</em>, грани будут <em>a</em>, <em>aa</em>, <em>aaa</em>, <em>aaaa</em>, но <em>aaaaa</em> гранью не будет.<br>
К чему собственно разгон: с помощью вычисления массива граней (он же таблица префиксов и суффиксов) реализуется главная фишка алгоритма — <strong>таблица сдвигов паттерна поиска</strong>.</p><br>
<h3 id="tablica-sdvigov-patterna-poiska">Таблица сдвигов паттерна поиска</h3><br>
<p>Есть например у нас паттерн поиска <strong>abaaba</strong>.</p><br>
<ol>
<li>Берем первый символ строки (а) и ищем для него грань. Так как для него грани быть не может (потому что грань не может быть равна строке) то грань — 0.</li>
<li>Берем теперь два первых символа (ab) и ищем грань для них. Так как нет суффикса, который равен префиксу, то грань снова 0.</li>
<li>Берем подстроку aba и ищем максимальную грань для нее. Так как из префиксов и суффиксов совпадают только буквы «а», то максимальная грань — 1.</li>
</ol><br>
<p>Повторять до конца.</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Код поиска граней</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function findBorders(pattern: string): number[] {
    const borders = new Array(pattern.length);
    borders[0] = 0;

    let currentIndex = 0;

    for (var i = 1; i &lt; pattern.length; i++) {
        while (currentIndex &gt; 0 &amp;&amp; pattern[currentIndex] !== pattern[i]) {
            currentIndex = borders[currentIndex - 1];
        }

        if (pattern[currentIndex] === pattern[i]) {
            currentIndex++;
        }

        borders[i] = currentIndex;
    }

    return borders;
}</code></pre></div>
                    </div><br>
<p>Результат должен быть вот такой:</p><br>
<p><img src="https://habrastorage.org/webt/ez/uy/tf/ezuytfywyo_mncbfbfwy2skxtqm.png" alt="image"></p><br>
<p>Для чего были нужны все эти манипуляции? Сейчас поясню.</p><br>
<p>Массив граней это градообразующее предприятие всего алгоритма: его задача сказать нам, откуда продолжать сравнивать, если вдруг наш процесс сравнения строки собьется.</p><br>
<h3 id="hod-poiska">Ход поиска</h3><br>
<p><img src="https://habrastorage.org/webt/oe/cp/bk/oecpbknc37iyvgdnshtcq8bdrpw.png" alt="image"></p><br>
<p>Что здесь происходит:<br>
Мы сравниваем наш текст <em>T</em> с паттерном <em>P</em>. Первые два символа текста совпали с паттерном, но третий символ <em>T</em> и <em>P</em> не совпали (<code>T[2] != P[2]</code>). Значит смотрим в наш массив граней <em>br</em>. Ага, грань <code>br[2]</code> имеет длину 0. Значит сдвигаем <em>P</em> на 2 символа вправо (длина совпавшего участка за вычетом длины грани плюс сдвиг на единичку: <code>2 - 1 + 1</code>).</p><br>
<p>Передвинули, проверяем символ еще раз:<code>T[2] != P[0]</code>, хорошо, тогда сдвигаем паттерн еще на <code>0 - 0 + 1</code>.</p><br>
<p>Дальше совпадает еще три символа и так далее.</p><br>
<p>Таким образом, зная структуру нашего паттерна мы можем оптимизировать количество сравнений и не возвращаться к уже проверенным участкам строки.</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Код алгоритма поиска</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function getSubstringKMP(text: string, pattern: string): number[] {
    const borders = findBorders(pattern);
    const result = [];

    let compareIndex = 0;

    for (let i = 0; i &lt; text.length; i++) {
        while (compareIndex &gt; 0 &amp;&amp; text[i] !== pattern[compareIndex]) {
            compareIndex = borders[compareIndex - 1];
        }

        if (text[i] === pattern[compareIndex]) {
            compareIndex++;
        }

        if (compareIndex === pattern.length) {
            result.push(i - compareIndex + 1);
            compareIndex = borders[pattern.length - 1];
        }
    }

    return result;
}</code></pre></div>
                    </div><br>
<h3 id="zamery-proizvoditelnosti">Замеры производительности</h3><br>
<p>Сравним производительность наивного алгоритма и нашей реализации КМП.</p><br>
<p>Текст:</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Очень длинная строка в 1024 символа</b>
                        <div class="spoiler_text"><p><code>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAACCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATAACCGATGTCTCGCCAAGATTTTGGCAACGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAA</code></p></div>
                    </div><br>
<p>Паттерн:<br>
<code>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTA</code></p><br>
<p>Замер происходит для всех четырех вхождений.</p><br>
<pre><code class="plaintext">getSubstringNaive x 2,961 ops/sec ±1.57% (88 runs sampled)
getSubstringKMP x 83,890 ops/sec ±0.48% (93 runs sampled)</code></pre><br>
<p>Выходит так, что КМП быстрее почти в 27 раз.</p><br>
<p>Напомню, что наивный алгоритм сравнивает последовательность в строке с паттерном <strong>полностью</strong>, то есть, если в какой-то момент он видит, что происходит несовпадение, то он все равно сравнивает до конца, надеясь на чудо. Ну выходит, что это тупой алгоритм, а не наивный.</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Очень наивный алгоритм</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function getSubstringNaive(text: string, pattern: string): number[] {
    const result = [];

    for (let i = 0; i &lt;= text.length - pattern.length; i++) {
        let flag = true;
        // Ну о-о-о-очень наивный алгоритм
        for (let j = 0; j &lt; pattern.length; j++) {
            if (text[i + j] !== pattern[j]) {
                flag = false;
            }

            if (j === pattern.length - 1 &amp;&amp; flag) {
                result.push(i);
            }
        }
    }

    return result;
}</code></pre></div>
                    </div><br>
<p>По этому я предлагаю не избивать младенцев, а все таки сделать некоторую оптимизацию наивного алгоритма, и прерывать сравнение при первом расхождении последовательностей.</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Не очень наивный алгоритм</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function getSubstringNotSoNaive(text: string, pattern: string): number[] {
    const result = [];

    for (let i = 0; i &lt;= text.length - pattern.length; i++) {
        for (let j = 0; j &lt; pattern.length; j++) {
            if (text[i + j] !== pattern[j]) {
                break;
            }

            if (j === pattern.length - 1) {
                result.push(i);
            }
        }
    }

    return result;
}</code></pre></div>
                    </div><br>
<p>Повторим наши замеры:</p><br>
<pre><code class="plaintext">getSubstringNaive x 2,984 ops/sec ±0.75% (97 runs sampled)
getSubstringKMP x 89,802 ops/sec ±0.20% (94 runs sampled)
getSubstringNotSoNaive x 109,839 ops/sec ±0.52% (96 runs sampled)</code></pre><br>
<p>И вот мы <strong>в 1.2 раза</strong> обогнали КМП алгоритм.</p><br>
<h2 id="sravnenie-produktivnosti">Сравнение продуктивности</h2><br>
<p>Хорошо, допустим КМП работает медленнее, но давайте посчитаем количество сравнений каждого алгоритма. Для этого заведем глобальные счетчики и посчитаем каждое сделанное сравнение.</p><br>
<p>Код для всего этого безобразия будет выглядеть</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Вот так</b>
                        <div class="spoiler_text"><pre><code class="javascript">export class Counter {
    public get count(): number {
        return this._count;
    }

    public readonly name: string;
    private _count: number = 0;

    public constructor(name: string) {
        this.name = name;
    }

    public increase(): void {
        this._count++;
    }
}

const counterMap = new Map&lt;string, Counter&gt;();

export function createCounter(name: string): Counter {
    const counter = new Counter(name);

    counterMap.set(name, counter);

    return counter;
}

export function getAllCounters(): [string, Counter][] {
    return Array.from(counterMap.entries());
}

export function compare&lt;T&gt;(first: T, second: T, counter: Counter): boolean {
    counter.increase();

    return first === second;
}</code></pre></div>
                    </div><br>
<p>Засунем везде функцию <strong>compare</strong> и будем считать каждое фактическое сравнение символов.</p><br>
<p>Результат: </p><br>
<pre><code class="plaintext">getSubstringNaive: 36,556
getSubstringKMP: 1,422
getSubstringNotSoNaive: 1,434</code></pre><br>
<p>У КМП результат по количеству сравнений наименьший, ему в спину дышит не очень наивный алгоритм с разницей всего в 12 сравнений, а полный аутсайдер — наивный алгоритм.</p><br>
<p>Хорошо, мы сравнили скорость алгоритмов на одной конкретной строке, сравнили их продуктивность по сравнениям, а теперь давайте сравним это все на реальном тексте. Внимательный читатель, должен был заметить, что строка из предыдущего примера подозрительно похожа на последовательность ДНК, так вот, это потому что КМП алгоритм вообще ценился, а может быть и до сих пор ценится в биоинформатике, в плане поиска нуклеотидных последовательностей (Я даже нашел пару научных публикаций на этот счет).</p><br>
<p>Но как мне кажется среди людей читающих эту статью вряд ли попадется хоть сколько-нибудь значимое количество биоинформатиков, так что предлагаю проверить алгоритм на реальном тексте, чтобы оценить его прикладное значение для рядового программиста.</p><br>
<p>Проверять будем на отрывке из Войны и мира про злосчастный дуб.</p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Отрывок про дуб</b>
                        <div class="spoiler_text"><p>На краю дороги стоял дуб. Вероятно, в десять раз старше берез, составлявших лес, он был в десять раз толще, и в два раза выше каждой березы. Это был огромный, в два обхвата дуб, с обломанными, давно, видно, суками и с обломанной корой, заросшей старыми болячками. С огромными своими неуклюже, несимметрично растопыренными корявыми руками и пальцами, он старым, сердитым и презрительным уродом стоял между улыбающимися березами. Только он один не хотел подчиняться обаянию весны и не хотел видеть ни весны, ни солнца.</p><br>
<p>«Весна, и любовь, и счастие! — как будто говорил этот дуб. — И как не надоест вам все один и тот же глупый бессмысленный обман! Все одно и то же, и все обман! Нет ни весны, ни солнца, ни счастья. Вон смотрите, сидят задавленные мертвые ели, всегда одинакие, и вон и я растопырил свои обломанные, ободранные пальцы, где ни выросли они — из спины, из боков. Как выросли — так и стою, и не верю вашим надеждам и обманам» .</p><br>
<p>Князь Андрей несколько раз оглянулся на этот дуб, проезжая по лесу, как будто он чего-то ждал от него. Цветы и трава были и под дубом, но он все так же, хмурясь, неподвижно, уродливо и упорно, стоял посреди их.</p><br>
<p>«Да, он прав, тысячу раз прав этот дуб, — думал князь Андрей, — пускай другие, молодые, вновь поддаются на этот обман, а мы знаем жизнь, — наша жизнь кончена! » Целый новый ряд мыслей безнадежных, но грустно-приятных в связи с этим дубом возник в душе князя Андрея. Во время этого путешествия он как будто вновь обдумал всю свою жизнь и пришел к тому же прежнему, успокоительному и безнадежному, заключению, что ему начинать ничего было не надо, что он должен доживать свою жизнь, не делая зла, не тревожась и ничего не желая.</p></div>
                    </div><br>
<p>Найдем все упоминания слов:</p><br>
<ol>
<li>дуб</li>
<li>Андрей</li>
<li>обломанн</li>
</ol><br>
<h4 id="rezultaty">Результаты</h4><br>
<p><strong>Ops/sec</strong></p><br>
<div class="scrollable-table"><table>
<thead>
<tr>
<th>Алгоритм</th>
<th>дуб</th>
<th>Андрей</th>
<th>обломанн</th>
</tr>
</thead>
<tbody>
<tr>
<td>getSubstringNaive</td>
<td>40,037</td>
<td>18,639</td>
<td>13,853</td>
</tr>
<tr>
<td>getSubstringKMP</td>
<td>92,671</td>
<td>96,830</td>
<td>87,442</td>
</tr>
<tr>
<td>getSubstringNotSoNaive</td>
<td>120,648</td>
<td>133,204</td>
<td>107,128</td>
</tr>
</tbody>
</table></div><br>
<p><strong>Количество сравнений</strong></p><br>
<div class="scrollable-table"><table>
<thead>
<tr>
<th>Алгоритм</th>
<th>дуб</th>
<th>Андрей</th>
<th>обломанн</th>
</tr>
</thead>
<tbody>
<tr>
<td>getSubstringNaive</td>
<td>5,013</td>
<td>10,008</td>
<td>13,328</td>
</tr>
<tr>
<td>getSubstringKMP</td>
<td>1,741</td>
<td>1,688</td>
<td>1,832</td>
</tr>
<tr>
<td>getSubstringNotSoNaive</td>
<td>1,739</td>
<td>1,683</td>
<td>1,828</td>
</tr>
</tbody>
</table></div><br>
<h4 id="ochevidnye-i-ne-ochen-vyvody">Очевидные и не очень выводы</h4><br>
<p>Первый вывод и он же очевидный: чем больше сравнений, тем меньше скорость алгоритма.</p><br>
<p>Второй: КМП и не очень наивный алгоритм имеют практически одинаковое количество сравнений, но при этом разница в скорости примерно 35%.</p><br>
<p><strong>Давайте поподробнее</strong></p><br>
<p>Длина текста — 1673 символа. Мы фактически подтвердили сложность алгоритмов (хотя это от нас и не требовалось и не то чтобы кто-то в ней сомневался, но мне все равно приятно), потому что у наивного алгоритма количество сравнений изменяется примерно как <u>n * m</u>, а у остальных алгоритмов оно с определенной погрешностью держится около <u>n</u>, как и задумано.</p><br>
<p>Разница между КМП и не очень наивным алгоритмом такая большая оттого, что у КМП есть препроцессинг строки, а у его оппонента его нет. Кроме того, у КМП есть еще и накладные расходы на проверки массива граней, на входы и выходы из различных циклов и if'ов, но так как почти во всех случаях массив граней пустой, то получается, что порядок сравнений у обоих алгоритмов практически идентичный.</p><br>
<p>Но, внезапный твист: главная фишка этого алгоритма не скорость, а то, что он не делает повторных сравнений уже пройденных символов. Если вы сравните алгоритмы, то наивная и не очень реализации сравнивают строки посимвольно и при несовпадении передвигают индекс сравнения вперед и идут по новой смотреть уже проверенные символы, а КМП видит несовпадение и перекидывает индекс сравнения в соответствии с массивом граней и идет себе дальше.</p><br>
<p>Это значит, что если у нас есть огромный файл генома и условно старый компьютер с ограниченным размером оперативной памяти (а КМП был опубликован в 1977 году, когда компьютер стоил как ракета, а оперативной памяти в них было с гулькин нос), то мы можем постепенно считывать этот файл (или перфоленту) и в реальном времени сравнивать поступающие данные и нужной последовательностью.</p><br>
<h2 id="vyvod">Вывод</h2><br>
<p>Алгоритм очень занятный, но в прикладном значении он скорее всего бесполезен для 95% программистов, только если они не разрабатывают систему реального времени на каких-либо слабеньких устройствах.</p><br>
<p>Но в его основе лежит хитроумная идея, которая весьма наглядно показывает, что не стоит просто кидаться на амбразуру, а иногда нужно провести разведку и ознакомиться с тем, что имеешь.</p><br>
