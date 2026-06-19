/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

int main(int argc, char *argv[])
{

     Info<< "Tutorial 02" << nl
          << tab << "Basic OpenFOAM data structures" << nl
          << tab << "Hash Tables-> key-value container and Hash set" << nl << endl; // Similar to unordered_map in stl of c++
     // É o dicionário do python
     // A HashTable is useful when you need to associate a key with a value and retrieve it quickly, without caring about the order.
     // This container can also be Resized, shrinked, cleared and clearStorage 

     HashTable<label> patchNameToIDMap;

     patchNameToIDMap.insert("a", 0);
     patchNameToIDMap.insert("b", 1);
     patchNameToIDMap.insert("c", 2);
     patchNameToIDMap.insert("e", 10);
     patchNameToIDMap.insert("h", 20);

     Info<< "Initial hash table:" << nl;
     Info<< patchNameToIDMap << endl;

     Info<< "size     = " << patchNameToIDMap.size() << nl;
     Info<< "capacity = " << patchNameToIDMap.capacity() << nl << endl;

     // Safe lookup
     // operator[] retrieves an existing value.
     // It should only be used when the key is known to exist.
     Info<< "Value for key \"b\" = " << patchNameToIDMap["b"] << endl;

     // Safer pattern: guard with found().
     if (patchNameToIDMap.found("a"))
     {
          Info<< "patch ID for key \"a\" = " << patchNameToIDMap["a"] << nl;
     }

     // Even better but less syntax friendly: use find().
     {
          const HashTable<label>::const_iterator iter = patchNameToIDMap.find("b");

          if (iter.good())
          {
               Info << "Found with find(): "
                    << iter.key() << " -> " << iter.val() << nl;
          }
     }

     // Be carefull of the operator(). It does find-or-create. So if it does not find it will create
     Info<< nl << "Before operator() lookup:" << nl << patchNameToIDMap << endl;

     Info<< "patchNameToIDMap(\"ffff\") = " << patchNameToIDMap("ffff") << endl;

     Info<< "After operator() lookup:" << nl << patchNameToIDMap << endl;


     // Remove an entry.
     const Switch erased = patchNameToIDMap.erase("ffff");   // returns a bool with the success of the operation

     Info<< "erase(\"ffff\") removed entry? " << erased << nl;

     Info<< "After erase(\"ffff\"):" << patchNameToIDMap << endl;


     // insert() does not overwrite existing keys
     {
          const Switch ok = patchNameToIDMap.insert("b", 99);

          Info<< nl
               << "insert(\"b\", 99) succeeded? " << ok << nl
               << "Value for \"b\" is: "
               << patchNameToIDMap["b"] << nl;
     }

     // set() inserts or overwrites
     {
          const Switch ok = patchNameToIDMap.set("b", 99);

          Info<< nl
               << "set(\"b\", 99) succeeded? " << ok << nl
               << "Value for \"b\" is: "
               << patchNameToIDMap["b"] << nl;
     }


     // Loop over the container
     forAllConstIters(patchNameToIDMap, it)
     {
          Info<< "   " << it.key() << " -> " << it.val() << nl;
     }

     Info << endl;


     // Key order
     wordList unsortedKeys = patchNameToIDMap.toc();
     Info<< "unsorted keys = " << unsortedKeys << endl;

     wordList sortedKeys = patchNameToIDMap.sortedToc();
     Info<< "sortedKeys = " << sortedKeys << endl;

     Info<< "Printed sorted key-value:" << nl;

     forAll(sortedKeys, i)
     {
          const word& key = sortedKeys[i];

          Info<< "   " << key
               << " -> " << patchNameToIDMap[key]
               << nl;
     }


     // labelHashSet: stores unique integer labels with fast lookup
     labelList cellIDOfBoundaryFaces({5, 8, 5, 12, 8, 8, 30, 12});

     labelHashSet uniq(cellIDOfBoundaryFaces);

     Info<< "cellIDOfBoundaryFaces = " << cellIDOfBoundaryFaces << nl;

     Info<< "labelHashSet(List), sorted = " << uniq.sortedToc() << nl;


     // HashSet algebra
     labelHashSet candidate({5, 6, 7, 8});
     Info<< "candidate = " << candidate << nl;

     // Intersection:
     // Keep only entries contained in both HashSets.
     labelHashSet both(candidate);
     both &= uniq;

     Info<< "intersection = " << both.sortedToc() << nl;

     // Union:
     // Keep all entries from both HashSets.
     labelHashSet either(candidate);
     either |= uniq;

     Info<< "union = " << either.sortedToc() << nl;

     // Difference:
     // Keep candidate entries that are not in uniq.
     labelHashSet onlyCandidate(candidate);
     onlyCandidate -= uniq;

     Info<< "difference = " << onlyCandidate.sortedToc() << nl;

     // Symmetric difference:
     // Keep entries that are in one set or the other, but not both.
     labelHashSet notBoth(candidate);
     notBoth ^= uniq;

     Info<< "symmetric difference = " << notBoth.sortedToc() << nl;

    Info<< nl << "End" << nl;

    return 0;
}

// ************************************************************************* //
