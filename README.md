# WordDictionary

### Problem statement

Напишите нехитрую считалку частотного словаря.
Словом считается набор латинских букв, a-zA-Z. Любой (любой) другой символ считается пробелом. Регистр нужно привести. Сортировать нужно сначала по частоте, потом по алфавиту. Выводить тоже сначала частоту, потом слово. Вот пример.

```
$ cat in.txt
The time has come, the Walrus said,
to talk of many things...
$ freq in.txt out.txt
$ cat out.txt
    2 the
    1 come
    1 has
    1 many
    1 of
    1 said
    1 talk
    1 things
    1 time
    1 to
    1 walrus
```

### Run

Проект запускается обычным CMake-ом. После сборки исполняемый файл удволетворяет сигнатуру запуска выше:

```
$ ./main in.txt out.txt
```

### Comments

Если бы не условие на `Любой (любой)` символ, я бы использовал более красивый imbue у стримов с собственной маской для игнорирования нелатинских символов. Но к сожалению такой подход работает только для non-wide char:

```
struct letters_only: std::ctype<char>
{
    letters_only(): std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(std::ctype<char>::table_size, std::ctype_base::space);
        std::fill(&rc['A'], &rc['Z'+1], std::ctype_base::alpha);
	std::fill(&rc['a'], &rc['z'+1], std::ctype_base::alpha);
        return &rc[0];
    }
};

// ...
// something going here
// ...


// before reading from inputstream, imbue it
is.imbue(std::locale(std::locale("en_US.UTF-8"), new letters_only()));
```
