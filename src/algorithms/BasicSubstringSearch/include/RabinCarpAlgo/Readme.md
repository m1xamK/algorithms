## Алгоритм Рабина-Карпа

<h2>Устройство алгоритма</h2><br>
<p>Вообще в классической реализации используется полиномиальный хеш, но подойдет в общем-то любая кольцевая хеш-функция. Но мы возьмем полиномиальную версию.</p><br>
<p>Алгоритм крайне простой: берем хеш паттерна, берем хеш куска текста равного по длине, сравниваем их. Если равны, то проверяем их посимвольно, в противном случае — идем дальше.</p><br>
<p><img src="https://habrastorage.org/webt/3u/9a/ae/3u9aae-py9_2jnbrgxts9-vqrpu.png"></p><br>
<h3 id="chto-eto-vse-znachit">Что это все значит</h3><br>
<p>Все очень просто.</p><br>
<p>У нас есть двоичный алфавит, где a = 0, b = 1.</p><br>
<p>Вычислим хеш паттерна:</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/166/af0/006/166af00064e31cad8ababd808a09a5c1.svg" alt="$H(P) = 1 * 2^4 + 0 * 2^3 + 1 * 2^2 + 0 * 2^1 + 1 * 2^0 = 21$" data-tex="display"></math></p><br>
<p>Вычислим хеш подстроки T[0, 4].</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/34b/4c4/c0f/34b4c4c0f551ecaaf501ca47a403a789.svg" alt="$H(T[0, 4]) = 0 * 2^4 + 0 * 2^3 + 1 * 2^2 + 0 * 2^1 + 1 * 2^0 = 5$" data-tex="display"></math></p><br>
<p>Они не совпадают, значит двигаем паттерн на символ правее.</p><br>
<p>Вычислим хеш подстроки T[1, 5].</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/ace/706/87e/ace70687eca927a6cd9d5b2de0091f7a.svg" alt="$H(T[1, 5]) = (H(T[0, 4]) - 0 * 2^4) * 2 + 0 * 2^0 = 10$" data-tex="display"></math></p><br>
<p>Хеши подстроки и паттерна снова не совпадают, значит двигаем паттерн еще на символ правее.</p><br>
<p>Вычислим хеш подстроки T[2, 6].</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/350/506/399/3505063990a9dd25960a756535c71497.svg" alt="$H(T[2, 6]) = (H(T[1, 5]) - 0 * 2^4) * 2 + 1 * 2^0 = 21$" data-tex="display"></math></p><br>
<p>Хеши совпали, значит проверяем этот участок посимвольно.</p><br>
<h3 id="raschet-hesha">Расчет хеша</h3><br>
<p>Чтобы сопоставить две строки, мы по факту превращаем их в числа простым переводом в произвольную систему счисления, где позиция символа это разряд, его код это значение разряда, а мощность алфавита это количество символов в кодировке (вообще это не обязательно, за мощность алфавита можно брать любое число больше единицы, но тогда коллизии будут встречаться чаще. Чем больше число, тем лучше, но главное не упереться в переполнение<strong>:)</strong>).</p><br>
<p>В общем виде расчет хеша будет выглядеть примерно вот так:</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/bed/422/a11/bed422a119f847b667fd0b03847b1db0.svg" alt="$H(P) = p[0] * x^{m-1} + p[1] * x^{m-2} + ... + p[m-1] * x^0$" data-tex="display"></math></p><br>
<p><math><img src="https://habrastorage.org/getpro/habr/formulas/3c8/da9/48a/3c8da948a52085be728f76fe67e197d3.svg" alt="$H(P)$" data-tex="inline"></math> — хеш паттерна<br>
<math><img src="https://habrastorage.org/getpro/habr/formulas/4cc/fd4/32e/4ccfd432ea4f2a64f3a5c8c7378517af.svg" alt="$x$" data-tex="inline"></math> — некоторое натуральное число, например мощность алфавита.</p><br>
<p>Теперь давайте посчитаем хеш реальной строки. Возьмем строку <strong>Pattern</strong> и для наглядности за <strong>x</strong> возьмем мощность семибитной таблицы ASCII — <strong>128</strong>.</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/acc/718/3d8/acc7183d8965bc5d9a736b788b330268.svg" alt="$H(Pattern) = 80 * 128^6 + 97 * 128^5 + 116 * 128^4 + 116 * 128^3 \\ + 101 * 128^2 + 114 * 128^1 + 110 * 128^0$" data-tex="display"></math></p><br>
<p>Результат: <strong>355 207 998 962 030</strong></p><br>
<p>Выглядит многовато. Чтобы записать такое число в двоичном виде понадобится 49 разрядов, а у нас из исходных данных всего лишь паттерн длинной 7 символов и урезанная кодировка ASCII. Если мы возьмем восьмибитную версию, то будет уже переполнение даже на 64-х битных системах. Так что решить этот вопрос нам помогут <strong>схема Горнера</strong> и <strong>модульная арифметика</strong>.</p><br>
<h3 id="shema-gornera">Схема Горнера</h3><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/28d/04b/d11/28d04bd11fa0a2f299bfab615c2ac707.svg" alt="$H(P) = p[m-1] * x^{m-1} + p[m-2] * x^{m-2} + ... + p[0] * x^0 = \\ (...(p[m-1] * x + p[m-2]) * x + ... + p[1]) * x + p[0]$" data-tex="display"></math></p><br>
<p>Ее задача помочь нам избавиться от возведения в степень, так как возведение в степень относительно прожорливая арифметическая операция. Кроме того, без схемы Горнера алгоритм хеширования станет менее оптимальным. Так как у нас будет большое количество дублирующихся вычислений.</p><br>
<p>Да и никакая модульная арифметика нам не поможет, если у нас паттерн длиной 128 ASCII-символов. В таком случае, при обычном возведении в степень, у нас для хеширования первого символа в паттерне будет использоваться число <math><img src="https://habrastorage.org/getpro/habr/formulas/cf1/862/739/cf186273957a7382f98c27fac327ab6d.svg" alt="$2^{1024}$" data-tex="inline"></math>, а это, как вы понимаете, много.</p><br>
<h3 id="modulnaya-arifmetika">Модульная арифметика</h3><br>
<p>Для того чтобы избежать переполнения, но при этом получать корректные результаты хеширования мы для всех промежуточных результатов вычислений будем брать остаток от деления.</p><br>
<p>Таким образом, наш конечный алгоритм должен выглядеть примерно вот так:</p><br>
<p></p><p><math><img src="https://habrastorage.org/getpro/habr/formulas/b39/0a3/899/b390a389986cf6c4f1d9749dd3495fec.svg" alt="$H(P) = (((...((p[m-1] * x + p[m-2])\mod q) * x \\ + ... + p[1]) \mod q) * x + p[0]) \mod q$" data-tex="display"></math></p><br>
<p>На всех промежуточных этапах мы получим значения не превышающие<br>
<math><img src="https://habrastorage.org/getpro/habr/formulas/c0e/f9f/7b6/c0ef9f7b62bf86417b44bd8f8d40e493.svg" alt="$p_{max} * (x + 1)$" data-tex="inline"></math>.</p><br>
<p>Но тут есть один нюанс:</p><br>
<blockquote>Когда тебе удается впихнуть невпихуемое, ты злишь бога коллизий</blockquote><br>
<h3 id="pobeg-ot-boga-kolliziy">Побег от бога коллизий</h3><br>
<p>Если начать забуриваться в изыскания на тему коллизий в кольцевых хеш-функциях, то натуральным образом можно оттуда не выбраться. Если кратко, то число <strong>q</strong> должно быть большим и простым. А если поподробнее то вот:</p><br>
<h4 id="popodrobnee">Поподробнее</h4><br>
<p>У нас есть текст <math><img src="https://habrastorage.org/getpro/habr/formulas/3e4/9fb/584/3e49fb58474f899dddcab78289ef7d69.svg" alt="$t[0...n]$" data-tex="inline"></math> длиной <math><img src="https://habrastorage.org/getpro/habr/formulas/f01/75a/f31/f0175af31bbb28b00d40cbf07d219e44.svg" alt="$len = n + 1$" data-tex="inline"></math>. Если мы возьмем <math><img src="https://habrastorage.org/getpro/habr/formulas/c07/a31/113/c07a3111335d7facc4ae7769133094bc.svg" alt="$q &gt; len^c$" data-tex="inline"></math>, где <math><img src="https://habrastorage.org/getpro/habr/formulas/888/670/b81/888670b8101985774255301905c18b10.svg" alt="$c &gt; 2$" data-tex="inline"></math>, то вероятность коллизии будет менее, чем <math><img src="https://habrastorage.org/getpro/habr/formulas/f03/6cb/b56/f036cbb567061d5cd96c40612370a4f3.svg" alt="$1/n^{c - 2}$" data-tex="inline"></math></p><br>
<p>Если пробежаться по первой тысяче простых чисел и построить график <math><img src="https://habrastorage.org/getpro/habr/formulas/893/167/b25/893167b251ad1246864d0ee39a2f0ecb.svg" alt="$N(Q)$" data-tex="inline"></math>, где <math><img src="https://habrastorage.org/getpro/habr/formulas/9aa/e08/704/9aae087046a60218262bab4a00522adc.svg" alt="$N$" data-tex="inline"></math> это количество коллизий, то будет вот:</p><br>
<p><img src="https://habrastorage.org/webt/4f/30/il/4f30il5dyztrwxa97yf0gzzajaa.png" alt="вот"></p><br>
<p>Здесь я провел проверку на отрывке про дуб из Войны и мира, где искал строку <strong>обломанн</strong>. Да паттерн не очень большой, числа тоже не самые огромные, но зато мы можем посмотреть динамику количества коллизий. И как это не тривиально — мы получили обычную асимптоту. Ну и как мы можем заметить после 7000 самое худшее, что мы получаем это 1 коллизию. Конечно не факт, что дальше не будет какого-нибудь всплеска. Но начиная с 2000 самое худшее, что у нас было это 4 коллизии на текст 1671 символа.</p><br>
<p>Все логично, чем больше простое число, тем меньше мы скукоживаем хеш, тем меньше коллизий. Ведь когда мы берем диапазон чисел <math><img src="https://habrastorage.org/getpro/habr/formulas/b80/560/771/b80560771af3db501904933da14f1207.svg" alt="$[0; 2^{1024}]$" data-tex="inline"></math>, (а примерно такой хеш мы можем получить без модульной арифметики), и пытаемся его ужать в диапазон <math><img src="https://habrastorage.org/getpro/habr/formulas/f05/e30/c3b/f05e30c3b93c8328b91eeda7ebc0418e.svg" alt="$[0, 2^{32}-1]$" data-tex="inline"></math>, то очевидно, что мы должны за это чем-то заплатить. И цена этому коллизии.</p><br>
<h2 id="kod-algoritma">Код алгоритма</h2><br>
<pre><code class="javascript">export function getSubstringRK(text: string, pattern: string): number[] {
    const result = [];

    const alphabetSize = 256;
    const mod = 9973;

    let patternHash = pattern.charCodeAt(0) % mod;
    let textHash = text.charCodeAt(0) % mod;

    let firstIndexHash = 1;

    for(let i = 1; i &lt; pattern.length; i++)
    {
        patternHash *= alphabetSize;
        patternHash += pattern.charCodeAt(i);
        patternHash %= mod;

        textHash *= alphabetSize;
        textHash += text.charCodeAt(i);
        textHash %= mod;

        firstIndexHash *= alphabetSize;
        firstIndexHash %= mod;
    }

    for (let i = 0; i &lt;= text.length - pattern.length; i++) {
        if (patternHash === textHash &amp;&amp; compareText(text, i, pattern)) {
            result.push(i);
        }

        if (i === text.length - pattern.length) break;

        textHash -= (text.charCodeAt(i) * firstIndexHash) % mod;
        textHash += mod;
        textHash *= alphabetSize;
        textHash += text.charCodeAt(i + pattern.length);
        textHash %= mod;
    }

    return result;
}

function compareText(text: string, index: number, pattern: string): boolean {
    for (let i = 0; i &lt; pattern.length; i++) {
        if (pattern[i] !== text[index + i]) {
            return false;
        }
    }

    return true;
}
</code></pre><br>
<h2 id="zamery-proizvoditelnosti">Замеры производительности</h2><br>
<p>Конкурсы все те же:</p><br>
<ul>
<li>Худший случай.</li>
<li>Строка с маломощным алфавитом.</li>
<li>Реальный текст.</li>
</ul><br>
<h3 id="oruschie-stroki">Орущие строки</h3><br>
<p>Замеры, где и текст и паттерн состоят только из буквы &quot;а&quot;.</p><br>
<p>Текст: строка длинной 1024 символа<br>
Образец: строка длинной 32 символа</p><br>
<h4 id="opssec">Ops/sec</h4><br>
<pre><code class="plaintext">getSubstringNaive x 9,141
getSubstringKMP x 84,419
getSubstringNotSoNaive x 9,587
getSubstringBMBadCharacter x 9,103
getSubstringRK x 9,975</code></pre><br>
<h4 id="kolichestvo-sravneniy">Количество сравнений</h4><br>
<pre><code class="plaintext">getSubstringNaive : 31,776
getSubstringKMP : 2,047
getSubstringNotSoNaive : 31,776    
getSubstringBMBadCharacter : 31,776
getSubstringRK : 32,769 </code></pre><br>
<p>Алгоритм Рабина-Карпа по сложности в худшем случае имеет сложность <math><img src="https://habrastorage.org/getpro/habr/formulas/ac3/7d5/1db/ac37d51db7de582ffae9bafb87b6f5ec.svg" alt="$O(n * m)$" data-tex="inline"></math>, по времени работы ничем сильно не выделяется, но при этом делает больше сравнений. Ведь перед тем как сверять строку мы сначала должны сверить хеш. Так что здесь наш подопытный аутсайдер.</p><br>
<h3 id="psevdo-dnk">Псевдо ДНК</h3><br>
<p>Строка состоящая из 1024 символов алфавита [TGAC]. </p><br>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Строка ДНК</b>
                        <div class="spoiler_text"><p>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAACCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATAACCGATGTCTCGCCAAGATTTTGGCAACGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAA</p></div>
                    </div><br>
<p>Образец: <code>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTA</code>. (37 символов)</p><br>
<h4 id="opssec-1">Ops/sec</h4><br>
<p>getSubstringNaive x 6,349<br>
getSubstringKMP x 156,780<br>
getSubstringNotSoNaive x 189,694<br>
getSubstringBMBadCharacter x 199,476<br>
getSubstringRK x 229,361</p><br>
<h4 id="kolichestvo-sravneniy-1">Количество сравнений</h4><br>
<pre><code class="plaintext">getSubstringNaive : 36,556
getSubstringKMP : 1,422
getSubstringNotSoNaive : 1,434    
getSubstringBMBadCharacter : 925
getSubstringRK : 1,136</code></pre><br>
<p>Несмотря на то, что алгоритм Рабина-Карпа на втором месте, по количеству сравнений, он опережает Бойера-Мура. Ну в общем-то БМ с эвристикой плохого символа не так эффективен на сгенерированных строках.</p><br>
<h3 id="voyna-i-mir">Война и мир</h3><br>
<p>Текст:</p><br>
<div class="spoiler" role="button" tabindex="0">
<b class="spoiler_title">Отрывок про дуб</b>
<div class="spoiler_text"><p>На краю дороги стоял дуб. Вероятно, в десять раз старше берез, составлявших лес, он был в десять раз толще, и в два раза выше каждой березы. Это был огромный, в два обхвата дуб, с обломанными, давно, видно, суками и с обломанной корой, заросшей старыми болячками. С огромными своими неуклюже, несимметрично растопыренными корявыми руками и пальцами, он старым, сердитым и презрительным уродом стоял между улыбающимися березами. Только он один не хотел подчиняться обаянию весны и не хотел видеть ни весны, ни солнца.</p><br>
<p>«Весна, и любовь, и счастие! — как будто говорил этот дуб. — И как не надоест вам все один и тот же глупый бессмысленный обман! Все одно и то же, и все обман! Нет ни весны, ни солнца, ни счастья. Вон смотрите, сидят задавленные мертвые ели, всегда одинакие, и вон и я растопырил свои обломанные, ободранные пальцы, где ни выросли они — из спины, из боков. Как выросли — так и стою, и не верю вашим надеждам и обманам» .</p><br>
<p>Князь Андрей несколько раз оглянулся на этот дуб, проезжая по лесу, как будто он чего-то ждал от него. Цветы и трава были и под дубом, но он все так же, хмурясь, неподвижно, уродливо и упорно, стоял посреди их.</p><br>
<p>«Да, он прав, тысячу раз прав этот дуб, — думал князь Андрей, — пускай другие, молодые, вновь поддаются на этот обман, а мы знаем жизнь, — наша жизнь кончена! » Целый новый ряд мыслей безнадежных, но грустно-приятных в связи с этим дубом возник в душе князя Андрея. Во время этого путешествия он как будто вновь обдумал всю свою жизнь и пришел к тому же прежнему, успокоительному и безнадежному, заключению, что ему начинать ничего было не надо, что он должен доживать свою жизнь, не делая зла, не тревожась и ничего не желая.</p></div>
                    </div><br>
<p>Паттерны:</p><br>
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
<td>57,320</td>
<td>29,506</td>
<td>21,596</td>
</tr>
<tr>
<td>getSubstringKMP</td>
<td>149,516</td>
<td>163,727</td>
<td>129,087</td>
</tr>
<tr>
<td>getSubstringNotSoNaive</td>
<td>161,560</td>
<td>176,117</td>
<td>136,640</td>
</tr>
<tr>
<td>getSubstringBMBadCharacter</td>
<td>246,769</td>
<td>376,072</td>
<td>409,002</td>
</tr>
<tr>
<td>getSubstringRK</td>
<td>153,172</td>
<td>155,100</td>
<td>152,668</td>
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
<tr>
<td>getSubstringBMBadCharacter</td>
<td>601</td>
<td>327</td>
<td>283</td>
</tr>
<tr>
<td>getSubstringBMGoodSuffix</td>
<td>1,692</td>
<td>1,680</td>
<td>1,690</td>
</tr>
</tbody>
</table></div><br>
<p>На реальном тексте алгоритм держит планку по <math><img src="https://habrastorage.org/getpro/habr/formulas/ac3/7d5/1db/ac37d51db7de582ffae9bafb87b6f5ec.svg" alt="$O(n * m)$" data-tex="inline"></math>, его производительность примерно как у КМП алгоритма и ± такое же количество сравнений.</p><br>
<h2 id="vyvody">Выводы</h2><br>
<p>Это далеко не самый шустрый алгоритм чтения, но у него есть одна крутая фишка: он может в неточный поиск. Так как он не делает сравнения символов напрямую, то он может шустро искать в потоковом режиме примеры вхождений определенного паттерна. Значит мы можем сделать систему, которая будет удалять все знаки препинания, переводить текст в нижний регистр и искать вхождение абзаца в текст. Да, если поизголяться, то это можно сделать и без РК алгоритма, но тогда это выйдет не так оптимально по времени и памяти.</p></div></div> <!----> <!----></div> <!----> <!----></div></div>
