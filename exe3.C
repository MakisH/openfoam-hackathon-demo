#include "fvCFD.H"

int main(int argc, char *argv[]) {
  HashTable<label> fieldIndex;

  fieldIndex.insert("p", 0);
  fieldIndex.insert("U", 1);
  fieldIndex.insert("T", 2);
  fieldIndex.insert("k", 7);
  fieldIndex.insert("epsilon", 15);

  Info << "fieldIndex.size() = " << fieldIndex.size() << endl;
  Info << "fieldIndex.capacity() = " << fieldIndex.capacity() << endl;
  Info << "fieldIndex['T'] = " << fieldIndex["T"] << endl;

  // Safer pattern: guard with found().
  if (fieldIndex.found("k")) {
    Info << "patch ID for key \"k\" = " << fieldIndex["k"] << nl;
  }

  Info << "Iterator for U" << endl;
  {
    const HashTable<label>::const_iterator iter = fieldIndex.find("U");

    if (iter.good()) {
      Info << "Found with find(): " << iter.key() << " -> " << iter.val() << nl;
    }
  }

  {
    const Switch ok = fieldIndex.set("rho", 42);

    Info << nl << "set(\"rho\", 42) succeeded? " << ok << nl
         << "Value for \"rho\" is: " << fieldIndex["rho"] << nl;
  }

  {
    const Switch ok = fieldIndex.insert("U", 99);

    Info << nl << "insert(\"U\", 99) succeeded? " << ok << nl
         << "Value for \"U\" is: " << fieldIndex["U"] << nl;
  }

  {
    const Switch ok = fieldIndex.set("U", 99);

    Info << nl << "set(\"U\", 99) succeeded? " << ok << nl
         << "Value for \"U\" is: " << fieldIndex["U"] << nl;
  }

  {
    // Remove an entry.
    const Switch erased = fieldIndex.erase(
        "T"); // returns a bool with the success of the operation

    Info << "erase(\"T\") removed entry? " << erased << nl;

    Info << "After erase(\"T\"):" << fieldIndex << endl;
  }

  forAllConstIters(fieldIndex, it) {
    Info << "   " << it.key() << " -> " << it.val() << nl;
  }

  // Key order
  wordList unsortedKeys = fieldIndex.toc();
  Info << "unsorted keys = " << unsortedKeys << endl;

  wordList sortedKeys = fieldIndex.sortedToc();
  Info << "sortedKeys = " << sortedKeys << endl;

  Info << "Printed sorted key-value:" << nl;

  forAll(sortedKeys, i) {
    const word &key = sortedKeys[i];

    Info << "   " << key << " -> " << fieldIndex[key] << nl;
  }

  labelList faceCells({3, 9, 3, 14, 9, 9, 25, 14});

  labelHashSet B(faceCells);

  Info << "labelHashSet(List), sorted = " << B.sortedToc() << nl;

  const labelHashSet A({3, 4, 9, 25, 40});

  // Intersection:
  // Keep only entries contained in both HashSets.
  labelHashSet both(A);
  both &= B;

  Info << "intersection = " << both.sortedToc() << nl;

  // Union:
  // Keep all entries from both HashSets.
  labelHashSet either(A);
  either |= B;

  Info << "union = " << either.sortedToc() << nl;

  // Difference:
  // Keep candidate entries that are not in uniq.
  labelHashSet onlyCandidate(A);
  onlyCandidate -= B;

  Info << "difference = " << onlyCandidate.sortedToc() << nl;

  return 0;
}