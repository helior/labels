**Labels** are simply strings with machine-names. They are translatable (via i18n_strings), user-editable, and exportable. They provide sufficient support for the CTools context system and Views.

The accompanied **Label Field** module implements a reference field that allows Labels to be associated with Entities via the Field API. This association can replace Taxonomy as a means to imply structure; since labels have machine-names, configuration (like panels or views) will never have to export with references to term IDs.

Other implementations could include auto-complete form widgets, label "sets" to imply coherency among a group of labels, etc.