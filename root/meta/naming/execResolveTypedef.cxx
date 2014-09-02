#include <stdio.h>
#include <TClassEdit.h>

// See also roottest/meta/naming/execCheckNaming.C

// The role of ResolveTypedef is to remove typedef and should be given
// an almost normalized name.  The main purpose of this test is to
// insure that nothing is removed and no stray space is added.
// However, (at least for now), it is allowed to remove some spaces
// but does not have to remove them (this is the job of ShortType
// or the name normalization routine).

namespace A1 { namespace B2 { namespace C3 { typedef int what; } } }
namespace NS { typedef int IntNS_t; }

class Object
{
public:
   struct Inside {};
   typedef long value_t;
};

namespace NS {
   template <typename T, typename Q = Object> class Inner
   {

   };
   typedef ::Object Object;
}

template <typename T> class Wrapper
{
public:
   typedef T value_t;
   typedef const T const_value_t;
   typedef NS::Inner<T,Object> Point_t;
   typedef NS::Inner<T>        PointDefault_t;

   T fOne;
   value_t fTwo;
};

bool testing(const char *expected, const std::string &result)
{
   static int count = 0;
   ++count;

   if (result == expected) {
      printf("Test %d The result is correct: %s\n",count, expected);
      return true;
   } else {
      printf("Error test %d the result is %s instead of %s\n",count,result.c_str(),expected);
      return false;
   }
}

int execResolveTypedef()
{
   testing("const int",TClassEdit::ResolveTypedef("const int"));
   testing("const int",TClassEdit::ResolveTypedef("const Int_t"));
   testing("const Long64_t",TClassEdit::ResolveTypedef("const long long"));
   testing("const Long64_t",TClassEdit::ResolveTypedef("const Long64_t"));

   testing("const int&",TClassEdit::ResolveTypedef("const int&"));
   testing("const int&",TClassEdit::ResolveTypedef("const Int_t&"));
   testing("const Long64_t&",TClassEdit::ResolveTypedef("const long long&"));
   testing("const Long64_t&",TClassEdit::ResolveTypedef("const Long64_t&"));

   testing("const int*",TClassEdit::ResolveTypedef("const int*"));
   testing("const int*",TClassEdit::ResolveTypedef("const Int_t*"));
   testing("const Long64_t*",TClassEdit::ResolveTypedef("const long long*"));
   testing("const Long64_t*",TClassEdit::ResolveTypedef("const Long64_t*"));

   testing("const int*&",TClassEdit::ResolveTypedef("const int*&"));
   testing("const int*&",TClassEdit::ResolveTypedef("const Int_t*&"));
   testing("const Long64_t*&",TClassEdit::ResolveTypedef("const long long*&"));
   testing("const Long64_t*&",TClassEdit::ResolveTypedef("const Long64_t*&"));

   testing("const int*const&",TClassEdit::ResolveTypedef("const int*const&"));
   testing("const int*const&",TClassEdit::ResolveTypedef("const Int_t* const &"));
   testing("const Long64_t*const&",TClassEdit::ResolveTypedef("const long long* const  &"));
   testing("const Long64_t*const&",TClassEdit::ResolveTypedef("const Long64_t*const&"));


   testing("int",TClassEdit::ResolveTypedef("A1::B2::C3::what"));
   testing("const int",TClassEdit::ResolveTypedef("const NS::IntNS_t"));

   testing("long",TClassEdit::ResolveTypedef("Object::value_t"));
   testing("long",TClassEdit::ResolveTypedef("Wrapper<long>::value_t"));
   testing("long",TClassEdit::ResolveTypedef("Wrapper<Long_t>::value_t"));
   testing("long",TClassEdit::ResolveTypedef("NS::Object::value_t"));

   testing("const long",TClassEdit::ResolveTypedef("Wrapper<long>::const_value_t"));
   testing("const long",TClassEdit::ResolveTypedef("Wrapper<Long_t>::const_value_t"));
   testing("const long",TClassEdit::ResolveTypedef("Wrapper<const long>::value_t"));
   testing("const long",TClassEdit::ResolveTypedef("Wrapper<const Long_t>::value_t"));

   testing("Object::Inside",TClassEdit::ResolveTypedef("NS::Object::Inside"));
   testing("Object",TClassEdit::ResolveTypedef("NS::Object"));

   // Known failure: the Double32_t is not yet propagated to the template's typedef :(
   // testing("Double32_t",TClassEdit::ResolveTypedef("Wrapper<Double32_t>::value_t"));

   testing("NS::Inner<long,Object>",TClassEdit::ResolveTypedef("Wrapper<long>::Point_t"));
   // 10.
   testing("NS::Inner<long,Object>",TClassEdit::ResolveTypedef("Wrapper<long>::PointDefault_t"));
   testing("NS::Inner<long,Object>",TClassEdit::ResolveTypedef("Wrapper<Long_t>::Point_t"));
   testing("NS::Inner<long,Object>",TClassEdit::ResolveTypedef("Wrapper<Long_t>::PointDefault_t"));

   testing("vector<long>",TClassEdit::ResolveTypedef("vector<Long_t>",true));
   testing("long",TClassEdit::ResolveTypedef("vector<Long_t>::value_type",true));

   testing("pair<vector<long>,int>",TClassEdit::ResolveTypedef("pair<vector<Long_t>,vector<Int_t>::value_type>",true));
   testing("pair<vector<long>,long>",TClassEdit::ResolveTypedef("pair<vector<Long_t>,vector<Long_t>::value_type>",true));

   testing("pair<pair<long,vector<int> >,long>",TClassEdit::ResolveTypedef("pair<pair<Long_t,vector<int>>,vector<Long_t>::value_type>",true));
   testing("pair<pair<long,vector<int> >,long>",TClassEdit::ResolveTypedef("pair<pair<Long_t,vector<int> >,vector<Long_t>::value_type>",true));

   testing("pair<vector<long>,long*>",TClassEdit::ResolveTypedef("pair<vector<long>,vector<long>::value_type*>",true));
   testing("pair<vector<long>,long*>",TClassEdit::ResolveTypedef("pair<vector<Long_t>,vector<Long_t>::value_type*>",true));

   testing("int",TClassEdit::ResolveTypedef("Int_t"));
   testing("Long64_t",TClassEdit::ResolveTypedef("Long64_t"));
   testing("Long64_t",TClassEdit::ResolveTypedef("long long"));
   testing("vec<Long64_t>",TClassEdit::ResolveTypedef("vec<Long64_t>"));
   testing("vec<Long64_t>",TClassEdit::ResolveTypedef("vec<long long>"));
   testing("Long64_t",TClassEdit::ResolveTypedef("vector<Long64_t>::value_type"));
   testing("Long64_t",TClassEdit::ResolveTypedef("vector<long long>::value_type"));

   testing("_Rb_tree_iterator<pair<const unsigned int,TGLPhysicalShape*> >::_Base_ptr*",TClassEdit::ResolveTypedef("_Rb_tree_iterator<pair<const unsigned int,TGLPhysicalShape*> >::_Base_ptr*"));
   testing("_Rb_tree_iterator<pair<const unsigned int,TGLPhysicalShape*> >::_Base_ptr*",TClassEdit::ResolveTypedef("_Rb_tree_iterator<pair<const UInt_t,TGLPhysicalShape*> >::_Base_ptr*"));

   // Known failure: the Long64_t is not yet propagated to the template's typedef :(
   // testing("NS::Inner<Long64_t,Object>",TClassEdit::ResolveTypedef("Wrapper<Long64_t>::Point_t"));

   printf("Starting GetNormalizedName tests\n");

   std::string output;
   TClassEdit::GetNormalizedName(output,"Wrapper<long>::Point_t");
   testing("NS::Inner<long,Object>",output);

   TClassEdit::GetNormalizedName(output,"Wrapper<Long_t>::Point_t");
   testing("NS::Inner<long,Object>",output);

   TClassEdit::GetNormalizedName(output,"Wrapper<long long>::Point_t");
   testing("NS::Inner<Long64_t,Object>",output);

   TClassEdit::GetNormalizedName(output,"Wrapper<long long>::PointDefault_t");
   testing("NS::Inner<Long64_t,Object>",output);

   TClassEdit::GetNormalizedName(output,"Wrapper<Long64_t>::Point_t");
   testing("NS::Inner<Long64_t,Object>",output);

   TClassEdit::GetNormalizedName(output,"Wrapper<Long64_t>::PointDefault_t");
   testing("NS::Inner<Long64_t,Object>",output);


   TClassEdit::GetNormalizedName(output,"pair<vector<Long_t>,vector<Long_t>::value_type>");
   testing("pair<vector<long>,long>",output);

   // Add an example like pair<...::type_t,int>

   return 0;
}