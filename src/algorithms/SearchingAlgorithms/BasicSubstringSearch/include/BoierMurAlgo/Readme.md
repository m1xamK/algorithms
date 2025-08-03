## Алгоритм Бойера-Мура ##

<h2 id="ustroystvo-algoritma">Устройство алгоритма</h2><br/>
<p>Он так же, как и большинство алгоритмов, двигает образец слева направо, но его отличительная черта в том, что он сравнивает его с текстом справа налево. Вроде бы ничего кардинально особенного, но искать быстро ему помогают две интересные эвристики.</p><br/>
<h3 id="pervaya-evristika">Первая эвристика</h3><br/>
Если символа на позиции T[m] в образце нет, то можем смело сдвигать образец за этот символ.<p>m – длина образца.</p><br/>
<p>Действительно, если даже мы хоть уприкладываемся образцом к участку текста, в котором нет нужного символа то, хоть убей, мы совпадения не получим. Зато если мы при первом сравнении обнаружили такой символ, то мы сдвигаем паттерн на <img src="https://habrastorage.org/getpro/habr/formulas/0cb/e1e/2f4/0cbe1e2f42f5e6bea0caffa1997a24d8.svg" alt="$m$" data-tex="inline"/> символов, а сравнивать начинаем уже символы P[m]  и T[m*2]. Звучит очень заманчиво, неправда ли?</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/bc/qn/vh/bcqnvhdgbh9u4c1nkejrl568y-4.png" data-src="https://habrastorage.org/webt/bc/qn/vh/bcqnvhdgbh9u4c1nkejrl568y-4.png"/></p><br/>
<p>Но если же символ на позиции T[m] есть в P, то следует P передвинуть так, чтобы под T[m] оказалось самое правое вхождение этого символа.</p><br/>
<p>Тут тоже все понятно: покуда в паттерне вхождение символа левее, то совпадений не будет, а самое правое вхождение мы выбираем, чтобы ненароком чего не упустить.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/ew/rb/8e/ewrb8ebfofhbeiv6ao4yxvikmow.png" data-src="https://habrastorage.org/webt/ew/rb/8e/ewrb8ebfofhbeiv6ao4yxvikmow.png"/></p><br/>
<h4 id="kod-sostavleniya-tablicy-plohih-simvolov">Код составления таблицы плохих символов</h4><br/>
<p>В оригинальном алгоритме создается массив длиной, равной длине кодировки, но в JS используется UTF-16, а в нее влазит до 1 112 064 символов, выходит накладненько. Важно понимать, что сам алгоритм появился в 1977 году, на 14 лет раньше того, когда люди решили взять все буквы на свете и запихнуть в одну табличку кодировки, так что ни у Бойера, ни у Мура не было сомнений, что создавать массив под всю кодировку это отличная идея. Все таки ASCII в зависимости от версии могла содержать от 128 до 256, так что это было оправданно.</p><br/>
<p>Но если его использовать в изначальной трактовке в наше время, то даже если у нас в паттерне будут все символы русского и английского алфавитов, то полезная заполненность такого массива для того же юникода будет (33 * 2 + 26 * 2 = 118) символов. А это примерно 0,01%, если учитывать весь потенциал юникода, если мы возьмем только заполненную его часть, то грубо говоря 0.12%. Это конечно в 12 раз лучше, но душу греет слабо.</p><br/>
<p>Так что я решил делать замеры на мапках, но ради чистоты эксперимента в конце статьи я выложу сравнительные замеры реализации на массиве и мапке.</p><br/>
<pre><code class="javascript">export function badCharacterHeuristic(pattern: string): Map&lt;string, number> {
    const result = new Map&lt;string, number>();

    for(let i = 0; i &lt; pattern.length; i++) {
       result.set(pattern[i], i);
    }

    return result;
}
</code></pre><br/>
<h3 id="hod-poiska">Ход поиска</h3><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/qk/il/q1/qkilq1ekyvs6epvtfwmsmdkoroe.png" data-src="https://habrastorage.org/webt/qk/il/q1/qkilq1ekyvs6epvtfwmsmdkoroe.png"/></p><br/>
<p>Сначала мы сравниваем символы T[8, 7, 6] и P[8, 7, 6] (именно 8, 7, 6, ведь сравнение идет в обратном порядке), далее видя на позиции T[6] вхождение символа «f», которого нет в образце, переносим образец на позицию 7. После этого сравниваем T[15] и P[8] — они не совпадают и поэтому ищем самое правое вхождение символа <strong>b</strong> в образец $P[5] и сдвигаем наш образец на m – q - 1 (длина образца — позиция символа — 1), далее история повторяется. Что примечательно, на данном примере совпадение нашлось за 4 прикладывания, красиво же звучит?</p><br/>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Код алгоритма поиска</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function getSubstringBMBadCharacter(text: string, pattern: string): number[] {
    const symbolIndexes = badCharacterHeuristic(pattern);

    const result = [];

    let shift = 0;

    while (shift &lt;= (text.length - pattern.length)) {
        let currentIndex = pattern.length - 1;

        while (currentIndex >= 0 &amp;&amp; pattern[currentIndex] === text[shift + currentIndex]) {
            currentIndex--;
        }

        if (currentIndex == -1) {
            result.push(shift);

            const indent = (shift + pattern.length &lt; text.length) 
                ? pattern.length - symbolIndexes.get(text[shift + pattern.length])! 
                : 1;

            shift += indent;
        } else {
            const indent = symbolIndexes.get(text[shift + currentIndex]) ?? -1;

            shift += Math.max(1, currentIndex - indent);
        }
    }

    return result;
}</code></pre></div>
                    </div><br/>
<h3 id="vtoraya-evristika">Вторая эвристика</h3><br/>
<p>Вторая эвристика немного похожа на КМП алгоритм за парой небольших исключений. Мы так же делаем таблицу граней для паттерна, но, во-первых, наше сравнение так же идет слева направо, во-вторых, мы подготавливаем массив сдвигов, который помогает нам определить самые выгодные переносы паттерна.</p><br/>
<p>При сравнении паттерна у нас может произойти три ситуации:</p><br/>
<h4 id="sluchay-1-vhozhdenie-sovpavshey-chasti-t-v-seredine-obrazca">Случай №1. Вхождение совпавшей части t в середине образца.</h4><br/>
<p>Образец может содержать несколько одинаковых последовательностей внутри самого себя, и в таком случае мы просто сдвигаем его так, чтобы следующая последовательность оказалась уже под проверенным текстом.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/bm/gv/u_/bmgvu_kars_40juzpuorg2vmqtq.png" data-src="https://habrastorage.org/webt/bm/gv/u_/bmgvu_kars_40juzpuorg2vmqtq.png"/></p><br/>
<p>Мы сравнили T[4, 3, 2] и P[4, 3, 2] и при этом совпали только символы 4 и 3 (ab). Следующее вхождение <strong>ab</strong> у нас идет с позиции 1, значит сдвигаем паттерн на 2 символа вправо. </p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/us/ga/pn/usgapngtitfosrce5ilztr6isyi.png" data-src="https://habrastorage.org/webt/us/ga/pn/usgapngtitfosrce5ilztr6isyi.png"/></p><br/>
<h4 id="sluchay-2-prefiks-obrazca-sovpadaet-s-suffiksom">Случай №2. Префикс образца совпадает с суффиксом.</h4><br/>
<p>Когда у нас нет вхождений совпавшей последовательности t в паттерне, мы можем попытаться приладить паттерн так, чтобы у нас совпал префикс с каким либо из суффиксов паттерна.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/sr/ts/1c/srts1cga2fpubuigibdjcrv_dec.png" data-src="https://habrastorage.org/webt/sr/ts/1c/srts1cga2fpubuigibdjcrv_dec.png"/></p><br/>
<p>Мы сравнили подстроки T[4 — 1] и P[4 — 1] и совпала подстрока <strong>bab</strong>. В паттерне больше такой комбинации символов нет, но мы можем приладить префикс ab, так как он является суффиксом совпавшей подстроки, поэтому сдвигаем паттерн на 3 символа вправо.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/ip/dw/o0/ipdwo0vbctnhzeyj1p0igpb8ftg.png" data-src="https://habrastorage.org/webt/ip/dw/o0/ipdwo0vbctnhzeyj1p0igpb8ftg.png"/></p><br/>
<h4 id="sluchay-3-nichego-ne-sovpadaet--edem-dalshe">Случай №3. Ничего не совпадает — едем дальше.</h4><br/>
<p>Когда два вышеперечисленных случая не наступают, мы просто перекидываем паттерн дальше.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/re/vs/d8/revsd8hhemjuabickkvlyhz-hmm.png" data-src="https://habrastorage.org/webt/re/vs/d8/revsd8hhemjuabickkvlyhz-hmm.png"/></p><br/>
<p>У нас произошло совпадение подстроки <strong>bab</strong>, но ни других ее вхождений нет, и на совпадение префикса мы рассчитывать не можем. Терять нам нечего, поэтому просто перекидываем паттерн на его же длину.</p><br/>
<p><img src="https://habrastorage.org/r/w1560/webt/_3/f-/5v/_3f-5vinkzl8ys4yayiitrgvgek.png" data-src="https://habrastorage.org/webt/_3/f-/5v/_3f-5vinkzl8ys4yayiitrgvgek.png"/></p><br/>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Код получения массива сдвигов</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function goodSuffixHeuristic(pattern: string): number[] {
    const shifts = new Array(pattern.length + 1).fill(0);
    const borderPositions = new Array(pattern.length + 1);

    findShiftsAndBorders(shifts, borderPositions, pattern);

    setShiftsForPrefix(shifts, borderPositions, pattern);

    return shifts;
}

function findShiftsAndBorders(shifts: number[], borderPositions: number[], pattern: string): void {
    let i = pattern.length;
    let j = pattern.length + 1;

    borderPositions[i] = j;

    while (i > 0) {
        while (j &lt;= pattern.length &amp;&amp; pattern[i - 1]!== pattern[j - 1]) {
            if (shifts[j] === 0) {
                shifts[j] = j - i;
            }

            j = borderPositions[j];
        }

        i--;
        j--;

        borderPositions[i] = j;
    }
}

function setShiftsForPrefix(shifts: number[], borderPositions: number[], pattern: string): void {
    let prefixBorder = borderPositions[0];

    for (let i = 0; i &lt;= pattern.length; i++) {
        if (shifts[i] === 0) {
            shifts[i] = prefixBorder;
        }

        if (i === prefixBorder) {
            prefixBorder = borderPositions[prefixBorder];
        }
    }
}
</code></pre></div>
                    </div><br/>
<p>Более подробно можно ознакомится с тем, что происходит в этом коде можно по <a href="https://www.geeksforgeeks.org/boyer-moore-algorithm-good-suffix-heuristic/" rel="nofollow noopener noreferrer">ссылке</a>, там все весьма подробно разобран как сам алгоритм, так и отдельные его части.</p><br/>
<h2 id="zamery-proizvoditelnosti">Замеры производительности</h2><br/>
<p>Замеры производительности я решил проводить со старыми участниками из предыдущей статьи для наглядности относительной производительности. Но на этот раз я решил сравнить работу алгоритма на самом худшем варианте поиска строк из возможных, а именно на строках состоящих из одного и того же символа.</p><br/>
<h3 id="oruschie-stroki">Орущие строки</h3><br/>
<p>Замеры, где и текст и паттерн состоят только из буквы "а".</p><br/>
<p>Текст: строка длинной 1024 символа<br/>
Образец: строка длинной 32 символа</p><br/>
<h4 id="opssec">Ops/sec</h4><br/>
<pre><code class="plaintext">getSubstringNaive: 8,785 
getSubstringKMP: 84,089
getSubstringNotSoNaive: 9,504
getSubstringBMBadCharacter: 9,100
getSubstringBMGoodSuffix: 10,884
</code></pre><br/>
<h4 id="kolichestvo-sravneniy">Количество сравнений</h4><br/>
<pre><code class="plaintext">getSubstringNaive : 31,776
getSubstringKMP : 2,047
getSubstringNotSoNaive : 31,776    
getSubstringBMBadCharacter : 31,776
getSubstringBMGoodSuffix : 31,776</code></pre><br/>
<p>Что видно по результатам: наивный алгоритм имеет сложность O(n * m), его результат от строки не зависит совсем, так что он у нас за контрольный образец; не очень наивный алгоритм в худшем случае имеет точно такую же сложность, ровно как и БМ; зато КМП проявил себя на их фоне очень хорошо, но у него и сложность O(n + m), а так же он делает в 15 раз меньше сравнений.</p><br/>
<h3 id="psevdo-dnk">Псевдо ДНК</h3><br/>
<p>Срока с алфавитом из [TGCA], иными словами со скудным набором символов.</p><br/>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Текст</b>
                        <div class="spoiler_text"><p>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAACCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATAACCGATGTCTCGCCAAGATTTTGGCAACGTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTAATTTGCAGTGCTATAAATCATCTCTAACGCTGGCTGTGCACCGCCACCCCAGCGGGAAGCCCATTTTTCCACTACCTCTGTTCCTGGTATAGTGCACTATATCGCCCGTAACCGATGTCTCGCCAAGATTTTGGCAACTTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAATTCCCGAGCAATCAGGTGGAGTCAGACCGATAGCTCTAATGGTTTACGTGAATGCATGGCGCCTATAGCTATGGGCAGAAA</p></div>
                    </div><br/>
<p>Образец: <code>GTAGTGTGTCTACGTCTTTCTTTGACAGTACCGCGTA</code></p><br/>
<h4 id="opssec-1">Ops/sec</h4><br/>
<pre><code class="plaintext">getSubstringNaive: 6,284
getSubstringKMP: 161,315
getSubstringNotSoNaive: 180,887
getSubstringBMBadCharacter: 75,085
getSubstringBMGoodSuffix: 508,159
</code></pre><br/>
<h4 id="kolichestvo-sravneniy-1">Количество сравнений</h4><br/>
<pre><code class="plaintext">getSubstringNaive : 36,556
getSubstringKMP : 1,422
getSubstringNotSoNaive : 1,434    
getSubstringBMBadCharacter : 925
getSubstringBMGoodSuffix : 363</code></pre><br/>
<p>Ожидаемо БМ с эвристикой плохого символа оказался похуже на данном замере, так как исходя из своей идеи он гораздо лучше работает на естественных текстах. Даже если в образце будут все символы из текста, то он сможет двигать паттерн на большее число шагов за раз, так как в естественном тексте все таки не случайное распределение символов.<br/>
Зато БМ со второй эвристикой чувствует себя как рыба в воде, потому что тексты со скудным набором символов это его специализация и он как раз таки используется в биоинформатике.<br/>
Несмотря на то, что в его основе лежит так же идея сравнения суффиксов, как и в КМП, он его обходит по скорости в три раза.<br/>
И это неспроста. КМП сначала сравнивает участок строки с паттерном и при разрыве совпадения переносит паттерн исходя из тех суффиксов, что он уже проверил. А БМ за счет большего анализа паттерна и сравнения справа налево при разрыве может перенести паттерн на большее число шагов, отчего у него и сравнений символа меньше в 5 раз и скорость выше в 3 раза.</p><br/>
<h3 id="voyna-i-mir">Война и мир</h3><br/>
<p>Текст:</p><br/>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Отрывок про дуб</b>
                        <div class="spoiler_text"><p>На краю дороги стоял дуб. Вероятно, в десять раз старше берез, составлявших лес, он был в десять раз толще, и в два раза выше каждой березы. Это был огромный, в два обхвата дуб, с обломанными, давно, видно, суками и с обломанной корой, заросшей старыми болячками. С огромными своими неуклюже, несимметрично растопыренными корявыми руками и пальцами, он старым, сердитым и презрительным уродом стоял между улыбающимися березами. Только он один не хотел подчиняться обаянию весны и не хотел видеть ни весны, ни солнца.</p><br/>
<p>«Весна, и любовь, и счастие! — как будто говорил этот дуб. — И как не надоест вам все один и тот же глупый бессмысленный обман! Все одно и то же, и все обман! Нет ни весны, ни солнца, ни счастья. Вон смотрите, сидят задавленные мертвые ели, всегда одинакие, и вон и я растопырил свои обломанные, ободранные пальцы, где ни выросли они — из спины, из боков. Как выросли — так и стою, и не верю вашим надеждам и обманам» .</p><br/>
<p>Князь Андрей несколько раз оглянулся на этот дуб, проезжая по лесу, как будто он чего-то ждал от него. Цветы и трава были и под дубом, но он все так же, хмурясь, неподвижно, уродливо и упорно, стоял посреди их.</p><br/>
<p>«Да, он прав, тысячу раз прав этот дуб, — думал князь Андрей, — пускай другие, молодые, вновь поддаются на этот обман, а мы знаем жизнь, — наша жизнь кончена! » Целый новый ряд мыслей безнадежных, но грустно-приятных в связи с этим дубом возник в душе князя Андрея. Во время этого путешествия он как будто вновь обдумал всю свою жизнь и пришел к тому же прежнему, успокоительному и безнадежному, заключению, что ему начинать ничего было не надо, что он должен доживать свою жизнь, не делая зла, не тревожась и ничего не желая.</p></div>
                    </div><br/>
<p>Паттерны:</p><br/>
<ol>
<li>дуб</li>
<li>Андрей</li>
<li>обломанн</li>
</ol><br/>
<h4 id="rezultaty">Результаты</h4><br/>
<p><strong>Ops/sec</strong></p><br/>
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
<td>57,470</td>
<td>30,058</td>
<td>22,072</td>
</tr>
<tr>
<td>getSubstringKMP</td>
<td>143,506</td>
<td>144,972</td>
<td>119,293</td>
</tr>
<tr>
<td>getSubstringNotSoNaive</td>
<td>151,456</td>
<td>176,935</td>
<td>144,634</td>
</tr>
<tr>
<td>getSubstringBMBadCharacter</td>
<td>43,934</td>
<td>79,005</td>
<td>95,611</td>
</tr>
<tr>
<td>getSubstringBMGoodSuffix</td>
<td>135,921</td>
<td>139,669</td>
<td>230,453</td>
</tr>
</tbody>
</table></div><br/>
<p><strong>Количество сравнений</strong></p><br/>
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
<td>1,643</td>
<td>1,627</td>
<td>914</td>
</tr>
</tbody>
</table></div><br/>
<p>В этом замере вышел занимательный результат. На первых двух замерах самым шустрым оказался все так же не очень наивный алгоритм. Но в конце всех обогнал БМ с эвристикой суффиксов.</p><br/>
<p>Честно говоря, я несколько большего ожидал от реализации БМ с плохим символом, я думал что он если и не обгонит реализацию с суффиксами, то хотя бы не сильно отстанет. Но он отстал ото всех кроме наивного алгоритма.</p><br/>
<p><strong>Но давайте разберемся в причинах этого провала:</strong></p><br/>
<p>Несмотря на наименьшее количество сравнений, БМ с плохим символом оказался таким медленным в наших замерах. А все потому что в нем используется мапка, а не массив. Дело в том, что мапка это дополнительный слой абстракции который съел весь возможный профит от работы алгоритма, потому что запрос элемента у массива и запись в него это абсолютно не то же самое, что и в мапку. Так что тут вина на мне.</p><br/>
<p>Но давайте попробуем его реабилитировать.</p><br/>
<p>Проведем сравнительные замеры реализации алгоритма на массиве и на мапке.</p><br/>
<p>Код реализации на мапке вы видели, а код реализации на массиве будет выглядеть вот так:</p><br/>
<div class="spoiler" role="button" tabindex="0">
                        <b class="spoiler_title">Первая эвристика на массиве</b>
                        <div class="spoiler_text"><pre><code class="javascript">export function badCharacterHeuristic(pattern: string, arraySize: number): number[] {
    const result = new Array(arraySize);

    for(let i = 0; i &lt; pattern.length; i++) {
       result[pattern.charCodeAt(i) % arraySize] = i;
    }

    return result;
}</code></pre></div>
                    </div><br/>
<p>У функции добавлен параметр <code>arraySize</code>, чтобы не дублировать ее кучу раз, так как замеры я проводил на 9 разных длинах массива. Запись в массив идет через остаток от деления, так что у данного решения будут коллизии и ложные срабатывания, но куда подеваться, у нас строка в юникоде, а мы пытаемся запихивать это дело все в массив так, чтобы работало, причем быстро и не сильно поджирало память понапрасну.</p><br/>
<p>Для проверки производительности я взял первую главу из Войны и мира, потому что она большая, на естественном языке и у нее сравнительно большой алфавит. Потому что что? Потому что в ней есть французский.</p><br/>
<p>Пример текста приводить не буду, статья, итак уже большая, но с параметрами ознакомимся.</p><br/>
<p>Длинна текста: 10520<br/>
Алфавит: <code>!'(),-.0123456789:;?ABCDEFGJLMNOQRS Vabcdefghijklmnopqrstuvxyz«»àèéêîôû́АБВГДЕЗИКМНО ПРСТУФЧШЭЯабвгдежзийклмнопрстуфхцчшщъыьэюя—</code><br/>
Размер алфавита: 128<br/>
Длины массивов для замера: 16, 32, 64, 128, 256, 1 024, 8 192, 23 770, 128 237<br/>
Длины паттернов: 1, 4, 8, 12, 24, 44, 80, 202</p><br/>
<p>Поясню про длины массивов: экстремально малые я взял для того, чтобы проверить влияние коллизий, а последние два размера это размер китайской кодировки GBK и размер заполненной части юникода (ну с запасом, конечно).</p><br/>
<p>Результаты замеров:</p><br/>
<p><strong>Для реализации на мапке (контрольный образец):</strong></p><br/>
<img src="https://habrastorage.org/r/w1560/webt/cs/xs/xl/csxsxlj0dp5pqjg0rv-07pzwhsm.png" data-src="https://habrastorage.org/webt/cs/xs/xl/csxsxlj0dp5pqjg0rv-07pzwhsm.png"/><br/>
<p><em>Серым помечена ячейка с выбросом.</em></p><br/>
<p>Производительность алгоритма изменяется строго от длинны образца, все как надо. Разумеется никакого массива тут не было, указанная длина это просто парный замер для соответствующего из второй таблицы.</p><br/>
<p><strong>Для реализации на массиве (опытный образец):</strong><br/>
<img src="https://habrastorage.org/r/w1560/webt/ov/ci/wy/ovciwy44_bjntsinoshiclmwvlu.png" data-src="https://habrastorage.org/webt/ov/ci/wy/ovciwy44_bjntsinoshiclmwvlu.png"/></p><br/>
<p><em>Красным выделены ячейки, где прослеживается тенденция к понижению производительности.</em></p><br/>
<h3 id="ochevidnye-i-ne-ochen-vyvody">Очевидные и не очень выводы</h3><br/>
<p>Как мы можем увидеть у нас есть просадки производительности в правом верхнем углу, назовем его угол коллизий, и в последних трех строках — поясе смерти.</p><br/>
<h4 id="proizvoditelnost">Производительность</h4><br/>
<p>Какую ячейку не возьми, кроме вышеуказанных мест (и то далеко не везде), у нее показатель лучше примерно в три раза. Все потому что лучше получить коллизию и сдвинуть паттерн чуть меньше и проверить немного больше символов, чем лезть в мапку. Запись и чтение из массива куда более низкоуровневая операция, чем аналоги с мапкой.</p><br/>
<h4 id="ugol-kolliziy">Угол коллизий</h4><br/>
<p>Как можно увидеть, коллизии это все таки проблема, но проявились они на экстремально малых массивах, а именно на массивах которые меньше алфавита в 8 раз и 4 раза. Даже массив размером в 2 раза меньше алфавита и тот не сильно просаживается в производительности. Но как мы можем заметить коллизии оказывают влияние не только исходя из размера массива, но и из размера паттерна, так как при возрастании длинны паттерна возрастает вероятность заработать больше коллизий, которые будут мешать делать полные переносы паттерна.</p><br/>
<p>Ну и в общем-то видно, что пик производительности приходится на массив длиной 128 символов, который по длинна подозрительно похож на алфавит. Конечно никто нам не гарантирует, что коды всего алфавита при делении на 128 дадут аккуратные остатки, прям чтобы от 0 до 128, но достаточно того, чтобы паттерн при укладке в массив влез и большинство символов не давали коллизий. Паттерн в 202 символа пробежал довольно шустро и не подавился, потому что в нем только русские символы, а в кодировке они идут по порядку и коллизий между собой давать не будут.</p><br/>

<h4 id="vyvody">Выводы</h4><br/>
<p>Если мы с вами добавим к сравнению реализацию на массивах к предыдущим замерам, то получим вот такой результат:</p><br/>
<p><strong>Псевдо ДНК:</strong></p><br/>
<pre><code class="plaintext">getSubstringNaive: 6,284
getSubstringKMP: 161,315
getSubstringNotSoNaive: 180,887
getSubstringBMBadCharacter: 75,085
getSubstringBMGoodSuffix: 508,159
</code></pre><br/>
<p><strong>Война и мир:</strong></p><br/>
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
<td>56,250</td>
<td>30,558</td>
<td>22,274</td>
</tr>
<tr>
<td>getSubstringKMP</td>
<td>160,154</td>
<td>157,744</td>
<td>119,464</td>
</tr>
<tr>
<td>getSubstringNotSoNaive</td>
<td>183,795</td>
<td>165,020</td>
<td>136,815</td>
</tr>
<tr>
<td>getSubstringBMBadCharacterMap</td>
<td>45,160</td>
<td>73,533</td>
<td>98,748</td>
</tr>
<tr>
<td>getSubstringBMBadCharacterArray</td>
<td>249,922</td>
<td>387,926</td>
<td>423,803</td>
</tr>
<tr>
<td>getSubstringBMGoodSuffix</td>
<td>151,375</td>
<td>139,733</td>
<td>230,233</td>
</tr>
</tbody>
</table></div><br/>
<p>Вы меня спросите почему, несмотря на то что данная реализация очевидно намного быстрее я выбрал для изначальных размеров реализацию на мапе? Ну раз вы дочитали до этого места я, наверное, должен вам ответить на этот абсолютно справедливый вопрос.</p><br/>
<p>Изначально я искренне заблуждаясь решил: "А почему бы собственно не использовать и мапку, ведь вроде как все равно быстро должно выйти, чего там?", хотя я понимал, что это привнесет накладные расходу, но по наивности их недооценил, потом я начал играться с массивами и получил вот такой вот результат.</p><br/>
<p>Но даже несмотря на это, я решил в первом примере оставить мапу, потому что в чистом виде этот алгоритм использовать просто не разумно, потому что, как мы с вами посмотрели, на больших массивах весь потенциал алгоритма сходит на нет, а версию с коллизиями я бы не рискнул назвать на сто процентов надежной. Да в моем примере она отработала хорошо, но я знал на каком тексте я работаю, какой у меня алфавит и какие будут паттерны. И в прод я бы его совать не стал, без полной уверенности в том, что я знаю какие тексты я буду на нем гонять.</p><br/>
<p>Ну в общем-то эта реализация ничуть не больше ближе к канону, хоть это и массив, но я по факту сделал всю туже хэш-таблицу, просто с примитивной хэш функцией и без нормальной обработки коллизий. А версия на мапке подходит ничуть не хуже для передачи главной идеи алгоритма.</p><br/>
<h2 id="slozhnost-algoritma">Сложность алгоритма</h2><br/>
<p>Так как анализ этого алгоритма процесс довольно нетривиальный, потому что скорость зависит от уникальности символов входящих в паттерн и от его длинны. Причем если паттерн длинный, а в нем находятся очень редкие символы, то скорость будет возрастать, хотя казалось бы длина ж растет, медленнее же должно быть.</p><br/>
<p>Если попытаться просто изложить расчет сложности для правила плохого символа, то это будет выглядеть примерно так:</p><br/>
<p>Для начала посчитаем количество вхождений всех символов:</p><br/>
<pre><code class="plaintext"> : 288    о: 136    н: 110    е: 101    и: 91     
а: 89     с: 66     т: 66     д: 57     в: 56     
р: 55     л: 51     м: 51     ,: 48     ы: 41     
у: 36     б: 35     я: 34     к: 32     з: 28    
ь: 24     п: 23     ж: 22     г: 15     ч: 14    
.: 13     й: 13     ю: 13     ш: 9      х: 8    
—: 7      э: 6      В: 5      !: 4      ц: 4    
А: 3      -: 2      «: 2      »: 2      К: 2   
Н: 2      Ц: 2      щ: 2      Д: 1      И: 1    
С: 1      Т: 1      Э: 1</code></pre><br/>
<p>Всего символов в строке у нас 1673.</p><br/>
<div class="scrollable-table"><table>
<thead>
<tr>
<th></th>
<th>дуб</th>
<th>Андрей</th>
<th>обломанн</th>
</tr>
</thead>
<tbody>
<tr>
<td>Частота</td>
<td>128</td>
<td>339</td>
<td>472</td>
</tr>
<tr>
<td>Вероятность</td>
<td>0.07</td>
<td>0.2</td>
<td>0.28</td>
</tr>
<tr>
<td>Мат. Ожидание полного переноса</td>
<td>2.79</td>
<td>4.8</td>
<td>5.76</td>
</tr>
</tbody>
</table></div><br/>
<p>Частота — суммарная частота появления уникальных символов из паттерна<br/>
Вероятность — вероятность того, что символ текста при сравнении присутствует в паттерне<br/>
Мат. Ожидание полного переноса — это ожидание того, что при отсутствии сравниваемого символа в паттерне мы сделаем полный перенос паттерна, рассчитывается как (1 - P) * m.</p><br/>
Но следует помнить, что если вероятность будет равна единице, то мы все равно переместимся на один символ:)<p>То есть условно при каждой проверке для слова дуб мы будем перемещаться в среднем на 2.8 символа за раз. Что радует эти данные коррелируют как и с замерами производительности, так и с замерами подсчетов.</p><br/>
<p>Ну и легко посчитать, что при P = 0, мы пролетим наш текст за O(n / m), а при P = 1 за O(n * m).</p><br/>
<p>Для эвристики хорошего суффикса я такое рассчитать не возьмусь:)</p><br/>
<p>Но вообще, считается, что для естественных текстов ее сложность в среднем стремится к O(n + m).</p><br/>
<h2 id="vyvody-1">Выводы</h2><br/>
<p>Этот алгоритм очень интересный. У него очень нетривиальная сложность и это позволяет очень хорошо пошевелить мозгами, чтобы понять, как он работает.</p><br/>
